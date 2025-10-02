package scanners

import (
	"strings"
	"text/template"

	"github.com/starter-go/base/lang"
)

type innerCHeaderFileCodeGenerator struct {
	builder *strings.Builder
	task    *ScanTask

	tagIfndef      string
	headerFileName string // the simple name of xxx.h
	fingerprint    lang.Hex

	params *CHeaderFileCodeGenParams

	templateFileHeader *template.Template
	templateFileItem   *template.Template
	templateFileFooter *template.Template
}

func (inst *innerCHeaderFileCodeGenerator) generate() (string, error) {

	builder := new(strings.Builder)
	task := inst.task
	steps := make([]func(task *ScanTask) error, 0)

	inst.builder = builder

	steps = append(steps, inst.doStepInit)
	steps = append(steps, inst.doStepPrepareParams)
	steps = append(steps, inst.doStepPrepareTemplates)

	steps = append(steps, inst.doStepFileHeader)
	steps = append(steps, inst.doStepFileItems)
	steps = append(steps, inst.doStepFileFooter)

	for _, fn := range steps {
		err := fn(task)
		if err != nil {
			return "", err
		}
	}

	code := builder.String()
	return code, nil
}

func (inst *innerCHeaderFileCodeGenerator) doStepInit(task *ScanTask) error {

	name := task.headerFile.GetName()

	inst.headerFileName = name
	inst.tagIfndef = inst.makeTagIfndef(name)
	inst.fingerprint = task.headerFileFingerprint

	return nil
}

func (inst *innerCHeaderFileCodeGenerator) makeTagIfndef(fileName string) string {

	str := "__" + strings.TrimSpace(fileName) + "__"

	str = strings.ReplaceAll(str, ".", "_")
	str = strings.ReplaceAll(str, "-", "_")

	return str
}

func (inst *innerCHeaderFileCodeGenerator) doStepPrepareParams(task *ScanTask) error {
	p := new(CHeaderFileCodeGenParams)

	p.FileName = inst.headerFileName
	p.Fingerprint = inst.fingerprint.String()
	p.TagIfndef = inst.tagIfndef

	p.TestFunctionName = "todo..."

	inst.params = p
	return nil
}

func (inst *innerCHeaderFileCodeGenerator) doStepPrepareTemplates(task *ScanTask) error {

	tempSet := task.templates

	t1, err := tempSet.findTemplate("header")
	if err != nil {
		return err
	}

	t2, err := tempSet.findTemplate("item")
	if err != nil {
		return err
	}

	t3, err := tempSet.findTemplate("footer")
	if err != nil {
		return err
	}

	inst.templateFileHeader = t1
	inst.templateFileItem = t2
	inst.templateFileFooter = t3
	return nil
}

func (inst *innerCHeaderFileCodeGenerator) doStepFileHeader(task *ScanTask) error {

	builder := inst.builder
	params := inst.params
	templ := inst.templateFileHeader

	return templ.Execute(builder, params)
}

func (inst *innerCHeaderFileCodeGenerator) doStepFileItems(task *ScanTask) error {

	builder := inst.builder
	params := inst.params
	templ := inst.templateFileItem
	list := task.unitTestFuncNameList

	for _, name := range list {
		p2 := params.Clone()
		p2.TestFunctionName = name
		err := templ.Execute(builder, p2)
		if err != nil {
			return err
		}
	}

	return nil
}

func (inst *innerCHeaderFileCodeGenerator) doStepFileFooter(task *ScanTask) error {

	builder := inst.builder
	params := inst.params
	templ := inst.templateFileFooter

	return templ.Execute(builder, params)
}

////////////////////////////////////////////////////////////////////////////////
// Params

type CHeaderFileCodeGenParams struct {

	// for global

	FileName    string
	TagIfndef   string
	Fingerprint string

	// for item
	TestFunctionName string
}

func (inst *CHeaderFileCodeGenParams) Clone() *CHeaderFileCodeGenParams {
	p1 := inst
	p2 := new(CHeaderFileCodeGenParams)
	*p2 = *p1
	return p2
}

////////////////////////////////////////////////////////////////////////////////
// EOF
