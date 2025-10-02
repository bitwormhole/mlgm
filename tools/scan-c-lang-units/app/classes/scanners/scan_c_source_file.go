package scanners

import (
	"fmt"
	"strings"

	"github.com/starter-go/afs"
)

type innerSourceFileContentScanner struct {
	task *ScanTask

	cTestFound bool // c:test is found
}

func (inst *innerSourceFileContentScanner) scan(file afs.Path, content string) error {

	rows := inst.split2rows(content)
	var err error = nil

	for idx, row := range rows {
		row = strings.TrimSpace(row)
		if row == "" {
			// skip
			err = nil
		} else if strings.HasPrefix(row, "//") {
			err = inst.handleRowComment(idx, row)
		} else {
			err = inst.handleRowNormalCCode(idx, row)
		}

		if err != nil {
			return err
		}
	}
	return nil
}

func (inst *innerSourceFileContentScanner) handleRowNormalCCode(idx int, row string) error {

	if inst.cTestFound {
		fn, err := inst.tryGetFunctionName(row)
		if (err == nil) && (fn != "") {
			inst.addFunctionName(fn)
		}
	}

	inst.cTestFound = false
	return nil
}

func (inst *innerSourceFileContentScanner) handleRowComment(idx int, row string) error {
	const token = "//c:test"
	str := inst.removeAllSpaceCharsFromString(row)
	if str == token {
		inst.cTestFound = true
	}
	return nil
}

func (inst *innerSourceFileContentScanner) addFunctionName(funcName string) {
	list := inst.task.unitTestFuncNameList
	list = append(list, funcName)
	inst.task.unitTestFuncNameList = list
}

func (inst *innerSourceFileContentScanner) tryGetFunctionName(row string) (string, error) {

	i1 := strings.IndexByte(row, '(')
	i2 := strings.LastIndexByte(row, ')')
	str := ""

	if (0 < i1) && (i1 < i2) {
		str = row[0:i1]
	} else {
		return "", fmt.Errorf("this row is NOT a function header")
	}

	const (
		ch0 = string(' ')
		ch1 = "\t"
		ch2 = "\n"
	)

	str = strings.ReplaceAll(str, ch0, ch2)
	str = strings.ReplaceAll(str, ch1, ch2)
	parts := strings.Split(str, ch2)
	lastPart := ""

	for _, part := range parts {
		if part == "" {
			continue
		}
		lastPart = part
	}

	if lastPart == "" {
		return "", fmt.Errorf("function name is not found")
	}
	return lastPart, nil
}

func (inst *innerSourceFileContentScanner) removeAllSpaceCharsFromString(str string) string {
	sb := strings.Builder{}
	chs := []byte(str)
	for _, b := range chs {
		if (b == '\t') || (b == ' ') || (b == '\r') || (b == '\n') {
			continue
		}
		sb.WriteByte(b)
	}
	return sb.String()
}

func (inst *innerSourceFileContentScanner) split2rows(content string) []string {
	const (
		ch1 = "\r"
		ch2 = "\n"
	)
	str := strings.ReplaceAll(content, ch1, ch2)
	return strings.Split(str, ch2)
}
