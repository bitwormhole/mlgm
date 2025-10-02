package scanners

import (
	"crypto/sha256"
	"fmt"
	"sort"
	"strings"

	"github.com/starter-go/afs"
	"github.com/starter-go/base/lang"
	"github.com/starter-go/vlog"
)

////////////////////////////////////////////////////////////////////////////////

type ScanTaskConfig struct {
	index int

	name string // the task name

	headerFile string

	headerFileFingerprint string

	codeGenTemplatesFile string

	sourceDir string
}

////////////////////////////////////////////////////////////////////////////////

type ScanTask struct {
	index int

	name string

	context *ScanContext

	config *ScanTaskConfig

	headerFile afs.Path // write to dst

	headerFileFingerprint lang.Hex // a hash-Fingerprint in target header file

	sourceDir afs.Path // read from src

	codeTemplatesFile afs.Path // templates file for code-gen

	templates *innerCodeGenTemplates

	code string // the generated code

	unitTestFuncNameList []string
}

func (inst *ScanTask) run() error {
	runner := new(innerScanTaskRunner)
	runner.task = inst
	return runner.run()
}

////////////////////////////////////////////////////////////////////////////////

type innerScanTaskRunner struct {
	task *ScanTask
}

func (inst *innerScanTaskRunner) run() error {

	task := inst.task
	steps := make([]func(task *ScanTask) error, 0)

	steps = append(steps, inst.doStepInit)
	steps = append(steps, inst.doStepScanSourceDir)
	steps = append(steps, inst.doStepPrintTestFunctionNameList)
	steps = append(steps, inst.doStepLoadCodeGenTemplates)
	steps = append(steps, inst.doStepGenerateCode)
	steps = append(steps, inst.doStepPrintGeneratedCode)
	steps = append(steps, inst.doStepLoadTargetHeaderFileFingerprint)
	steps = append(steps, inst.doStepCheckTargetHeaderFileFingerprint)
	steps = append(steps, inst.doStepWriteToHeaderFile)

	for _, fn := range steps {
		err := fn(task)
		if err != nil {
			return err
		}
	}
	return nil
}

func (inst *innerScanTaskRunner) doStepInit(task *ScanTask) error {

	ctx := task.context
	cfg1 := ctx.config
	cfg2 := task.config
	configFile := cfg1.file
	baseDir := configFile.GetParent()

	task.sourceDir = baseDir.GetChild(cfg2.sourceDir)
	task.headerFile = baseDir.GetChild(cfg2.headerFile)
	task.codeTemplatesFile = baseDir.GetChild(cfg2.codeGenTemplatesFile)

	return nil
}

func (inst *innerScanTaskRunner) doStepScanSourceDir(task *ScanTask) error {

	dir := task.sourceDir
	if !dir.IsDirectory() {
		return fmt.Errorf("no source dir: [%s]", dir.GetPath())
	}

	vlog.Info("===============================================================")
	vlog.Info("scan c-source dir:\n  %s", dir.GetPath())

	namelist := dir.ListNames()
	sort.Strings(namelist)

	for _, name := range namelist {
		child := dir.GetChild(name)
		if inst.isCLangSourceFile(child) {
			err := inst.scanContentOfCLangSourceFile(child)
			if err != nil {
				return err
			}
		}
	}

	return nil
}

func (inst *innerScanTaskRunner) isCLangSourceFile(file afs.Path) bool {
	if !file.IsFile() {
		return false
	}
	name := file.GetName()
	name = strings.ToLower(name)
	return strings.HasSuffix(name, ".c")
}

func (inst *innerScanTaskRunner) scanContentOfCLangSourceFile(file afs.Path) error {

	text, err := file.GetIO().ReadText(nil)
	if err != nil {
		return err
	}

	vlog.Info("scan c source file [%s]", file.GetPath())

	// size := len(text)
	// vlog.Info("    read %d bytes", size)

	scanner := new(innerSourceFileContentScanner)
	scanner.task = inst.task
	return scanner.scan(file, text)
}

func (inst *innerScanTaskRunner) doStepLoadTargetHeaderFileFingerprint(task *ScanTask) error {

	cfg := task.config
	fp1str := cfg.headerFileFingerprint
	fp := inst.parseHeaderFileFingerprint(fp1str)

	vlog.Info("target header file fingerprint: %s", fp)

	task.headerFileFingerprint = fp
	return nil
}

func (inst *innerScanTaskRunner) doStepCheckTargetHeaderFileFingerprint(task *ScanTask) error {

	fp := task.headerFileFingerprint
	file := task.headerFile
	txt, err := file.GetIO().ReadText(nil)
	if err != nil {
		return err
	}

	if !strings.Contains(txt, fp.String()) {
		const f = "no fingerprint [%s] in the c-header (*.h) file [%s]"
		return fmt.Errorf(f, fp.String(), file.GetPath())
	}

	return nil
}

func (inst *innerScanTaskRunner) makeDefaultHeaderFileFingerprint() lang.Hex {

	const nl = '\n'
	task := inst.task
	ctx := task.context
	file1 := ctx.config.file
	file2 := task.headerFile
	builder := new(strings.Builder)

	builder.WriteString(file1.GetPath())
	builder.WriteRune(nl)
	builder.WriteString(file2.GetPath())
	builder.WriteRune(nl)

	str := builder.String()
	sum := sha256.Sum256([]byte(str))
	return lang.HexFromBytes(sum[:])
}

func (inst *innerScanTaskRunner) parseHeaderFileFingerprint(str string) lang.Hex {

	str = strings.ToLower(str)
	str = strings.TrimSpace(str)

	fp := lang.Hex(str)
	bin := fp.Bytes()
	const bin_len_min = 8

	if (str == "") || (str == "auto") || (str == "default") || (len(bin) < bin_len_min) {
		return inst.makeDefaultHeaderFileFingerprint()
	}
	return lang.HexFromBytes(bin)
}

func (inst *innerScanTaskRunner) doStepLoadCodeGenTemplates(task *ScanTask) error {

	file := task.codeTemplatesFile
	templ := new(innerCodeGenTemplates)

	err := templ.loadFromXML(file)
	if err != nil {
		return err
	}

	task.templates = templ
	return nil
}

func (inst *innerScanTaskRunner) doStepGenerateCode(task *ScanTask) error {

	cg := new(innerCHeaderFileCodeGenerator)
	cg.task = task
	code, err := cg.generate()
	if err != nil {
		return err
	}

	task.code = code
	return nil
}

func (inst *innerScanTaskRunner) doStepPrintTestFunctionNameList(task *ScanTask) error {
	list := task.unitTestFuncNameList
	sort.Strings(list)
	count := len(list)
	vlog.Info("found %d function(s) of c:test:", count)
	for idx, name := range list {
		vlog.Info("   c_test_func[%d] : %s", idx, name)
	}
	return nil
}

func (inst *innerScanTaskRunner) doStepPrintGeneratedCode(task *ScanTask) error {

	code := task.code
	const tag = "---- Generated Code %s ----"

	vlog.Info(tag, "Begin")
	vlog.Info("\n%s", code)
	vlog.Info(tag, "End")

	return nil
}

func (inst *innerScanTaskRunner) doStepWriteToHeaderFile(task *ScanTask) error {

	return nil
}

////////////////////////////////////////////////////////////////////////////////
