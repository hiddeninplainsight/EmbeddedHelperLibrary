require_relative "find_files"

class UnityFixtureTestRunnerGenerator
	def initialize()
		@groups = []
	end

	def importfile(input_file)
		#Read the file
		File.open(input_file, 'r') do |input|
			findgroups(input)
		end
	end

	def findgroups(input_file)
		input_file.rewind
		source_raw = input_file.read
		source_scrubbed = source_raw.gsub(/\/\/.*$/, '')           # remove line comments
		source_scrubbed = source_scrubbed.gsub(/\/\*.*?\*\//m, '') # remove block comments
		lines = source_scrubbed.split(/(^\s*\#.*$)                 # Treat preprocessor directives as a logical line
								  | (;|\{|\}) /x)                  # Match ;, {, and } as end of lines

		lines.each_with_index do |line, index|
			if line =~ /(^TEST_GROUP\()(.*)(\))/
				group = $2.strip
				tests = findtests(lines, group)
				@groups << { :name => group, :tests => tests }
			end
		end
	end

	def findtests(lines, search_group)
		tests = []

		lines.each_with_index do |line, index|
			#find test groups
			if line =~ /(^TEST\()(.*)(,)(.*)(\))/
				group = $2.strip
				test = $4.strip

				if(search_group == group)
					#puts ["Found Test \"#{test}\" for group \"#{group}\""]
					tests << { :name => test }
				end
			end
		end

		return tests
	end

	def outputrunner(group, output = $stdout)
		output.puts("\nTEST_GROUP_RUNNER(#{group[:name]})")
		output.puts("{")
		group[:tests].each do |test|
			output.puts("\tRUN_TEST_CASE(#{group[:name]}, #{test[:name]});")
		end
		output.puts("}")
	end

	def outputrunalltests(output = $stdout)
		output.puts("\nstatic void RunAllTests()")
		output.puts("{")
		@groups.each do |group|
			output.puts("\tRUN_TEST_GROUP(#{group[:name]});")
		end
		output.puts("}")
	end

	def outputmain(output = $stdout)
		output.puts("\nint TestMain(int argc, char** argv)")
		output.puts("{")
		output.puts("\treturn UnityMain(argc, const_cast<const char**>(argv), RunAllTests);")
		output.puts("}")
	end

	def outputfile(output = $stdout)
		output.puts("#include \"unity_cpp.h\"")

		if @groups[0]
			@groups.each do |group|
				outputrunner(group, output)
			end
		end

		outputrunalltests(output)

		outputmain(output)
	end

end

if ($0 == __FILE__)

	file_list = FindFiles.new(ARGV)
	generator = UnityFixtureTestRunnerGenerator.new()

	file_list.GetFileList().each do |file|
		generator.importfile(file)
	end

	if(file_list.GetOutputFile() == "")
		generator.outputfile
	else
		File.open(file_list.GetOutputFile(), 'w') do |output|
			generator.outputfile(output)
		end
	end
end
