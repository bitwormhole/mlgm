package scanners

import (
	"bytes"
	"encoding/xml"

	"github.com/starter-go/afs"
)

type innerCodeGenTemplates struct {
}

func (inst *innerCodeGenTemplates) loadFromXML(file afs.Path) error {

	txt, err := file.GetIO().ReadText(nil)
	if err != nil {
		return err
	}

	// strings.TrimSpace(txt)

	rdr := bytes.NewBufferString(txt)

	dec := xml.NewDecoder(rdr)

	t, err := dec.Token()

	root := new(DomTemplates)

	err = dec.Decode(&root)

	// return fmt.Errorf("todo:  innerCodeGenTemplates.loadFromXML()  ... ")

	return err
}

////////////////////////////////////////////////////////////////////////////////

// type DomDocument struct {
// 	DomTemplates
// }

type DomTemplates struct {
	XMLName xml.Name `xml:"templates"`

	Templates []DomTemplate `xml:"templates"`
}

type DomTemplate struct {
	Name string

	Text string
}

////////////////////////////////////////////////////////////////////////////////
