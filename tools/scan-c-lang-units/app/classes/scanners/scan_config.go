package scanners

import (
	"fmt"
	"strings"

	"github.com/starter-go/afs"
	"github.com/starter-go/application/properties"
)

////////////////////////////////////////////////////////////////////////////////

type ScanConfig struct {
	fileName string

	file afs.Path

	props properties.Table

	tasks []*ScanTaskConfig
}

func (inst *ScanConfig) load(ctx *ScanContext) error {
	loader := new(myScanConfigLoader)
	loader.config = inst
	loader.context = ctx
	return loader.load()
}

////////////////////////////////////////////////////////////////////////////////

type myScanConfigLoader struct {
	config  *ScanConfig
	context *ScanContext
}

func (inst *myScanConfigLoader) load() error {

	ctx := inst.context
	cfg := ctx.config
	file := cfg.file

	txt, err := file.GetIO().ReadText(nil)
	if err != nil {
		return err
	}

	tab, err := properties.Parse(txt, nil)
	if err != nil {
		return err
	}

	const (
		keyScanClass = "scan.class"
		keyScanTasks = "scan.tasks"

		strScanClassWant = "c.lang.units"
	)

	t2 := tab.Getter().Required()

	strScanClassHave := t2.GetString(keyScanClass)
	strTaskNameList := t2.GetString(keyScanTasks)

	if strScanClassHave != strScanClassWant {
		const f = "bad scan.class value [key:'%s' want_value:'%s' have_value:'%s']"
		return fmt.Errorf(f, keyScanClass, strScanClassWant, strScanClassHave)
	}

	taskNameList, err := inst.parseTaskNameList(strTaskNameList)
	if err != nil {
		return err
	}

	for i, name := range taskNameList {
		tc, err := inst.loadTaskConfig(i, name, t2)
		if err != nil {
			return err
		}
		cfg.tasks = append(cfg.tasks, tc)
	}

	err = t2.Error()
	if err != nil {
		return err
	}

	cfg.props = tab
	return nil
}

func (inst *myScanConfigLoader) parseTaskNameList(str string) ([]string, error) {
	dst := []string{}
	src := strings.Split(str, ",")
	for _, name := range src {
		name = strings.TrimSpace(name)
		if name == "" {
			continue
		}
		dst = append(dst, name)
	}
	return dst, nil
}

func (inst *myScanConfigLoader) loadTaskConfig(index int, name string, props properties.Getter) (*ScanTaskConfig, error) {

	const (
		keyTaskScanDir          = "task.{n}.scan-dir"
		keyTaskWrite2hFile      = "task.{n}.write-to-h-file"
		keyTaskHeaderFileFinger = "task.{n}.target-header-file-fingerprint"
		keyTaskGenCodeTemplates = "task.{n}.gen-code-templates-file"
		token                   = "{n}"
	)
	key := ""

	key = strings.ReplaceAll(keyTaskScanDir, token, name)
	valueTaskScanDir := props.GetString(key)

	key = strings.ReplaceAll(keyTaskWrite2hFile, token, name)
	valueTaskWrite2hFile := props.GetString(key)

	key = strings.ReplaceAll(keyTaskHeaderFileFinger, token, name)
	valueTaskHeaderFileFinger := props.GetString(key)

	key = strings.ReplaceAll(keyTaskGenCodeTemplates, token, name)
	valueTaskGenCodeTemplates := props.GetString(key)

	err := props.Error()
	if err != nil {
		return nil, err
	}

	stc := new(ScanTaskConfig)
	stc.headerFile = valueTaskWrite2hFile
	stc.sourceDir = valueTaskScanDir
	stc.codeGenTemplatesFile = valueTaskGenCodeTemplates
	stc.headerFileFingerprint = valueTaskHeaderFileFinger
	stc.index = index
	stc.name = name
	return stc, nil
}

////////////////////////////////////////////////////////////////////////////////
