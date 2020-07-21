#!/usr/bin/python

import os
import sys

tests = ['2+2', '2+2_var', 'call_on_temp', 'compare', 'fac', \
 		 'if_else', 'interactive', 'modified', 'print_n_numbers', \
 		 'println', 'scopes', 'shadowed_modified', \
 		 'simple_call', 'two_classes_simple', 'two_classes']

ir_tests = ['if(a)', 'if_test']

failing_tests = ['undecl_var', 'local_scope']

def java_file(test):
	return test_id + '.java'

def dot_file(test):
	return test_id + '.dot'

def png_file(test):
	return test_id + '.png'

output_dir = "TestOutput"

executable = './bin/jc'

parse_ast_command = "{executable} ./JavaExamples/{test}.java --ast ./{dir}/{test}.dot"
parse_ir_command = "{executable} ./JavaExamples/{test}.java --ir ./{dir}/{test}.dot"

compile_and_run_command = "{executable} ./JavaExamples/{test}.java"
render_image_command = "dot -Tpng ./{dir}/{test}.dot -o {dir}/{test}.png"

def parse_ast_cmd(test):
	return parse_ast_command.format(executable=executable, test=test, dir=output_dir)

def parse_ir_cmd(test):
	return parse_ir_command.format(executable=executable, test=test, dir=output_dir)

def render_cmd(test, dir):
	return render_image_command.format(test=test, dir=dir)

def run_cmd(test):
	return compile_and_run_command.format(executable=executable, test=test)

def render_images(test, dir):
	print("[*] Rendering \'{}\'".format(test))
	stream = os.popen(render_cmd(test, dir))
	print(stream.read())

def run_single_test(test, ast, ir):
	print("-------------------------------------------")
	print("Running test \'{test}\'".format(test=test))

	if ast:
		stream = os.popen(parse_ast_cmd(test))
		print(stream.read())
	elif ir:
		stream = os.popen(parse_ir_cmd(test))
		print(stream.read())
	else:
		stream = os.popen(run_cmd(test))
		print(stream.read())

def main(png_dir, ast=False, ir=False):
	print("\n### Positive tests: ###\n")

	for test in tests:
		run_single_test(test, ast, ir)

	print("\n### Failing tests ###\n")

	for test in failing_tests:
		run_single_test(test, ast, ir)

	if ast or ir:
		for test in tests:
			render_images(test, png_dir)

def usage():
	print ("\tUsage: test.py [ast/ir]\n")

if __name__ == "__main__":
    ast = False
    ir = False
        
    if len(sys.argv) > 1:
        if sys.argv[1] == "ast":
        	ast = True
        elif sys.argv[1] == "ir":
        	ir = True

    path = output_dir
    main(path, ast, ir)
