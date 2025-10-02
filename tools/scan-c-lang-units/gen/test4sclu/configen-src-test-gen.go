package main4sclu
import (
    p156b125d5 "github.com/bitwormhole/mlgm/tools/scan-c-lang-units/src/test/golang/units"
     "github.com/starter-go/application"
)

// type p156b125d5.Unit1 in package:github.com/bitwormhole/mlgm/tools/scan-c-lang-units/src/test/golang/units
//
// id:com-156b125d5e421d90-units-Unit1
// class:
// alias:
// scope:singleton
//
type p156b125d5e_units_Unit1 struct {
}

func (inst* p156b125d5e_units_Unit1) register(cr application.ComponentRegistry) error {
	r := cr.NewRegistration()
	r.ID = "com-156b125d5e421d90-units-Unit1"
	r.Classes = ""
	r.Aliases = ""
	r.Scope = "singleton"
	r.NewFunc = inst.new
	r.InjectFunc = inst.inject
	return r.Commit()
}

func (inst* p156b125d5e_units_Unit1) new() any {
    return &p156b125d5.Unit1{}
}

func (inst* p156b125d5e_units_Unit1) inject(injext application.InjectionExt, instance any) error {
	ie := injext
	com := instance.(*p156b125d5.Unit1)
	nop(ie, com)

	


    return nil
}


