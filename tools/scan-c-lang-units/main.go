package main

import (
	"embed"
	"os"

	"github.com/bitwormhole/mlgm/tools/scan-c-lang-units/gen/main4sclu"
	"github.com/starter-go/application"
	"github.com/starter-go/starter"
)

const (
	theModuleName = "github.com/bitwormhole/mlgm/tools/scan-c-lang-units"
	theModuleVer  = "v0.0.0"
	theModuleRev  = 0
)

////////////////////////////////////////////////////////////////////////////////

const (
	theMainModuleResPath = "src/main/resources"
)

//go:embed "src/main/resources"
var theMainModuleResFS embed.FS

////////////////////////////////////////////////////////////////////////////////

func ModuleMain() application.Module {

	mb := new(application.ModuleBuilder)

	mb.Name(theModuleName)
	mb.Version(theModuleVer)
	mb.Revision(theModuleRev)

	mb.EmbedResources(theMainModuleResFS, theMainModuleResPath)

	mb = main4sclu.ExportComponents(mb)

	mb.Depend(starter.Module())

	return mb.Create()
}

////////////////////////////////////////////////////////////////////////////////

func main() {

	// xfs := files.FS()

	a := os.Args
	m := ModuleMain()
	i := starter.Init(a)

	i.MainModule(m)
	i.WithPanic(true).Run()
}
