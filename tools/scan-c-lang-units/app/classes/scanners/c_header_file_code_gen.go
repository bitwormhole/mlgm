package scanners

import (
	"fmt"
	"strings"
)

const (
	nl = "\n"
)

type innerCHeaderFileCodeGenerator struct {
	builder *strings.Builder
	task    *ScanTask

	tagIfndef      string
	headerFileName string // the simple name of xxx.h

	templateListBegin string
	templateListItem  string
	templateListEnd   string
}

func (inst *innerCHeaderFileCodeGenerator) generate() (string, error) {

	builder := new(strings.Builder)
	task := inst.task
	steps := make([]func(task *ScanTask) error, 0)

	inst.builder = builder

	steps = append(steps, inst.doStepInit)
	steps = append(steps, inst.doStep1FileBegin)
	steps = append(steps, inst.doStepAddFingerprint)

	steps = append(steps, inst.doStep2ListBegin)
	steps = append(steps, inst.doStep3ListItems)
	steps = append(steps, inst.doStep4ListEnd)
	steps = append(steps, inst.doStep5FileEnd)

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

	inst.templateListBegin = "void unit_test_case_list ()  {\n"
	inst.templateListItem = "  unit_test_case_list_item( \"%s\", %s);\n"
	inst.templateListEnd = "}\n"

	return nil
}

func (inst *innerCHeaderFileCodeGenerator) makeTagIfndef(fileName string) string {

	str := "__" + strings.TrimSpace(fileName) + "__"

	str = strings.ReplaceAll(str, ".", "_")
	str = strings.ReplaceAll(str, "-", "_")

	return str
}

func (inst *innerCHeaderFileCodeGenerator) doStep1FileBegin(task *ScanTask) error {
	builder := inst.builder

	builder.WriteString("// ")
	builder.WriteString(inst.headerFileName)
	builder.WriteString(nl)

	builder.WriteString("#ifndef ")
	builder.WriteString(inst.tagIfndef)
	builder.WriteString(nl)

	builder.WriteString("#define ")
	builder.WriteString(inst.tagIfndef)
	builder.WriteString(nl)

	return nil
}

func (inst *innerCHeaderFileCodeGenerator) doStepAddFingerprint(task *ScanTask) error {
	builder := inst.builder

	builder.WriteString("// fingerprint: ffffffffffffff")
	builder.WriteString(nl)

	return nil
}

func (inst *innerCHeaderFileCodeGenerator) doStep2ListBegin(task *ScanTask) error {
	builder := inst.builder

	builder.WriteString("// list begin")
	builder.WriteString(nl)

	return nil
}

func (inst *innerCHeaderFileCodeGenerator) doStep3ListItems(task *ScanTask) error {

	builder := inst.builder
	list := task.unitTestFuncNameList
	templ := inst.templateListItem
	line := ""

	for _, name := range list {

		// line := fmt.Sprintf("// test_func[%d] : %s", i, name)

		line = fmt.Sprintf(templ, name, name)

		builder.WriteString(line)
		builder.WriteString(nl)
	}

	return nil
}

func (inst *innerCHeaderFileCodeGenerator) doStep4ListEnd(task *ScanTask) error {

	builder := inst.builder

	builder.WriteString("// list end")
	builder.WriteString(nl)

	return nil
}

func (inst *innerCHeaderFileCodeGenerator) doStep5FileEnd(task *ScanTask) error {
	builder := inst.builder

	builder.WriteString("// file end")
	builder.WriteString(nl)

	builder.WriteString("#endif // ")
	builder.WriteString(inst.tagIfndef)
	builder.WriteString(nl)

	return nil
}
