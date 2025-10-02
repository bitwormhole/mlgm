package scanners

import "github.com/starter-go/afs"

type ScanContext struct {
	config *ScanConfig

	wkdir afs.Path

	tasks []*ScanTask
}
