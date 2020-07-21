### Mini Java Compiler ###

* New feature: generate and render IR (intermediate representation) with `test.py ir` command from root dir
* `test.py` runs 'positive' and 'failing' tests to show performance and precise compile-time errors when fails
* tests are located at `JavaExamples/` dir.
* when running with 'ast' or 'ir', `.dot` files with AST representation are outputted to `TestOutput/` dir
