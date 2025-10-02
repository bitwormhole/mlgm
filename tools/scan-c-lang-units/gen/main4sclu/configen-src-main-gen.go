package main4sclu
import (
    p3f74fbdd4 "github.com/bitwormhole/mlgm/tools/scan-c-lang-units/app/classes/scanners"
    p0d2a11d16 "github.com/starter-go/afs"
     "github.com/starter-go/application"
)

// type p3f74fbdd4.Scanner in package:github.com/bitwormhole/mlgm/tools/scan-c-lang-units/app/classes/scanners
//
// id:com-3f74fbdd45c81a23-scanners-Scanner
// class:
// alias:
// scope:singleton
//
type p3f74fbdd45_scanners_Scanner struct {
}

func (inst* p3f74fbdd45_scanners_Scanner) register(cr application.ComponentRegistry) error {
	r := cr.NewRegistration()
	r.ID = "com-3f74fbdd45c81a23-scanners-Scanner"
	r.Classes = ""
	r.Aliases = ""
	r.Scope = "singleton"
	r.NewFunc = inst.new
	r.InjectFunc = inst.inject
	return r.Commit()
}

func (inst* p3f74fbdd45_scanners_Scanner) new() any {
    return &p3f74fbdd4.Scanner{}
}

func (inst* p3f74fbdd45_scanners_Scanner) inject(injext application.InjectionExt, instance any) error {
	ie := injext
	com := instance.(*p3f74fbdd4.Scanner)
	nop(ie, com)

	
    com.AFS = inst.getAFS(ie)


    return nil
}


func (inst*p3f74fbdd45_scanners_Scanner) getAFS(ie application.InjectionExt)p0d2a11d16.FS{
    return ie.GetComponent("#alias-0d2a11d163e349503a64168a1cdf48a2-FS").(p0d2a11d16.FS)
}


