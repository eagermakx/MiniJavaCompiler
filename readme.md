### Mini Java Compiler ###

#### `test.py` 
`Usage:  <br/>
   test.py [ast/ir] [-c]` <br/>
	ast - render abstract syntax tree images <br>
	ir - render intermediate repreentation tree images <br>
	-c - canonize IR tree beforehand` <br>

* New feature: canonize IR tree (eliminate double call in binary expressions, linearize SEQ chains and eliminate ESEQ nodes
* New feature: generate and render IR (intermediate representation) with `test.py ir` command from root dir
* `test.py` runs 'positive' and 'failing' tests to show performance and precise compile-time errors when fails
* tests are located at `JavaExamples/` dir.
* when running with 'ast' or 'ir', `.dot` files with AST representation are outputted to `TestOutput/` dir

#### Check out 'fac' (factorial) test :)
