package main4sclu

import "github.com/starter-go/application"

//starter:configen(version="4")

func ExportComponents(mb *application.ModuleBuilder) *application.ModuleBuilder {

	fn := registerComponents

	mb.Components(fn)

	return mb
}
