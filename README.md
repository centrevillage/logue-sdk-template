# logue-sdk-template

### place the logue-sdk directory in same parent directory

```
$ ls your_work_dir

...
logue-sdk
logue-sdk-template
...
```

### generate custom oscillator project

```
./logue_gen osc your_osc_project_name
cd osc/projects/your_osc_project_name/
make -f Makefile_nts-1
make -f Makefile_minilogue-xd
make -f Makefile_prologue
```

### generate custom delfx project

```
./logue_gen delfx your_osc_project_name
cd delfx/projects/your_osc_project_name/
make -f Makefile_nts-1
make -f Makefile_minilogue-xd
make -f Makefile_prologue
```

### generate custom revfx project

```
./logue_gen revfx your_osc_project_name
cd revfx/projects/your_osc_project_name/
make -f Makefile_nts-1
make -f Makefile_minilogue-xd
make -f Makefile_prologue
```

### generate custom modfx project

```
./logue_gen modfx your_osc_project_name
cd modfx/projects/your_osc_project_name/
make -f Makefile_nts-1
make -f Makefile_minilogue-xd
make -f Makefile_prologue
```
