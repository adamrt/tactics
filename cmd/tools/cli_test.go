package main

import (
	"strings"
	"testing"
)

func TestBuildModuleAliases(t *testing.T) {
	want := map[string]string{
		"main": "main", "battle": "battle", "attack": "event-attack",
		"card": "event-card", "debugchr": "event-debugchr",
		"effect259": "effect-e259",
		"helpmenu":  "event-helpmenu", "require": "event-require",
		"equip": "event-equip", "etc": "event-etc", "jobstts": "event-jobstts",
		"option": "event-option", "bunit": "event-bunit",
		"opening": "opening",
		"small":   "event-small", "wldcore": "wldcore", "world": "world",
	}
	for name, moduleID := range want {
		if got := buildModuleAliases[name]; got != moduleID {
			t.Errorf("buildModuleAliases[%q] = %q, want %q", name, got, moduleID)
		}
	}
}

func TestCommandDispatchRejectsUnknownSelections(t *testing.T) {
	p := project{}
	tests := []struct {
		name string
		run  func() error
		want string
	}{
		{name: "build", run: func() error { return p.buildCommand([]string{"unknown"}) }, want: "unknown build module"},
		{name: "wip", run: func() error { return p.candidateCommand([]string{"unknown"}) }, want: "unknown wip action"},
		{name: "tools", run: func() error { return p.toolsCommand([]string{"unknown"}) }, want: "unknown tools action"},
	}
	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			err := test.run()
			if err == nil || !strings.Contains(err.Error(), test.want) {
				t.Fatalf("error = %v, want text %q", err, test.want)
			}
		})
	}
}
