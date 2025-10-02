package scanners

import (
	"fmt"
	"os"

	"github.com/starter-go/afs"
	"github.com/starter-go/application"
	"github.com/starter-go/vlog"
)

type Scanner struct {

	//starter:component

	AFS afs.FS //starter:inject("#")
}

func (inst *Scanner) Life() *application.Life {

	l := new(application.Life)

	l.OnCreate = inst.onCreate
	l.OnStart = inst.onStart
	l.OnDestroy = inst.onDestroy

	l.OnLoop = inst.onRun

	return l
}

func (inst *Scanner) onCreate() error {
	return nil
}

func (inst *Scanner) onStart() error {
	return nil
}

func (inst *Scanner) onDestroy() error {
	vlog.Info("done")
	return nil
}

func (inst *Scanner) onRun() error {

	// vlog.Warn("Scanner.onRun(...)")

	return inst.scan()
}

func (inst *Scanner) scan() error {

	ctx := new(ScanContext)
	steps := make([]func(ctx *ScanContext) error, 0)

	steps = append(steps, inst.doStepInit)
	steps = append(steps, inst.doStepLocateWkdir)
	steps = append(steps, inst.doStepLocateConfigFile)
	steps = append(steps, inst.doStepLoadConfigFile)
	steps = append(steps, inst.doStepScanCLangSourceFiles)

	for i, fn := range steps {
		vlog.Info("step[%d]:", i)
		err := fn(ctx)
		if err != nil {
			return err
		}
	}
	return nil
}

func (inst *Scanner) doStepInit(ctx *ScanContext) error {

	cfg := new(ScanConfig)

	cfg.fileName = "scan-c-lang-units.config"

	ctx.config = cfg

	return nil
}

func (inst *Scanner) doStepLocateWkdir(ctx *ScanContext) error {

	vlog.Info("locate working dir ...")

	dir, err := os.Getwd()
	if err != nil {
		return err
	}

	wkdir := inst.AFS.NewPath(dir)
	ctx.wkdir = wkdir

	vlog.Info("wkdir = %s", dir)

	return nil
}

func (inst *Scanner) doStepLocateConfigFile(ctx *ScanContext) error {

	cfg := ctx.config
	fileName := cfg.fileName
	wkdir := ctx.wkdir
	path := wkdir
	ttl := 0

	vlog.Info("look-up config file (%s) ...", fileName)

	for ttl = 99; ttl > 0; ttl-- {

		if path == nil {
			break
		}

		file := path.GetChild(fileName)

		if file.IsFile() {
			vlog.Info("find config file @(%s)", file.GetPath())
			cfg.file = file
			return nil
		}

		path = path.GetParent()
	}
	return fmt.Errorf("cannot find config file at wkdir (%s)", wkdir.GetPath())
}

func (inst *Scanner) doStepLoadConfigFile(ctx *ScanContext) error {

	vlog.Info("load config file ...")

	cfg := ctx.config
	return cfg.load(ctx)
}

func (inst *Scanner) doStepScanCLangSourceFiles(ctx *ScanContext) error {

	vlog.Info("scan c-source files ...")

	cfg := ctx.config
	src := cfg.tasks
	dst := ctx.tasks

	for i, stc := range src {
		task := new(ScanTask)
		task.config = stc
		task.context = ctx
		task.index = i
		task.name = stc.name

		err := task.run()
		if err != nil {
			return err
		}

		dst = append(dst, task)
	}

	return nil
}
