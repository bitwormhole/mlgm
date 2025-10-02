package scanners

import (
	"encoding/xml"
	"fmt"
	"text/template"

	"github.com/starter-go/afs"
)

type innerCodeGenTemplates struct {
	table map[string]*template.Template
}

func (inst *innerCodeGenTemplates) loadFromXML(file afs.Path) error {

	inst.reset()

	data, err := file.GetIO().ReadBinary(nil)
	if err != nil {
		return err
	}

	root := new(DomTemplates)
	err = xml.Unmarshal(data, root)
	if err != nil {
		return err
	}

	list := root.Templates
	for _, temp := range list {
		err = inst.loadTemplate(&temp)
		if err != nil {
			return err
		}
	}

	return nil
}

func (inst *innerCodeGenTemplates) loadTemplate(t *DomTemplate) error {

	name := t.Name
	text := t.Text
	table := inst.table

	templ, err := template.New(name).Parse(text)
	if err != nil {
		return err
	}

	table[name] = templ
	return nil
}

func (inst *innerCodeGenTemplates) reset() {
	inst.table = make(map[string]*template.Template)
}

func (inst *innerCodeGenTemplates) findTemplate(name string) (*template.Template, error) {
	tmp := inst.table[name]
	if tmp == nil {
		return nil, fmt.Errorf("no template with name: [%s]", name)
	}
	return tmp, nil
}

////////////////////////////////////////////////////////////////////////////////
// DOM

type DomTemplates struct {
	Templates []DomTemplate `xml:"template"`
}

type DomTemplate struct {
	Name string `xml:"name,attr"`

	Text string `xml:",chardata"`
}

////////////////////////////////////////////////////////////////////////////////
// EOF
