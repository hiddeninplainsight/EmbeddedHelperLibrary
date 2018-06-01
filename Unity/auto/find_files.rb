
class FindFiles
	def initialize(argv)
		@files = []
		@output_file = ""

		argv.each do |arg|
			if arg =~ /(.*)(.cpp)/
				@output_file = $1 + $2
				@output_file = File.join(File.expand_path(File.dirname(".")), @output_file)
			else
				AddDirectory(arg)
			end
		end

		if @files.length == 0
			AddDirectory()
		end
	end

	def AddDirectory(directory = "")
		if directory == ""
			directory="."
		end

		directory = File.expand_path(directory)
		test_filter = File.join(directory, "**", "*.cpp")

		test_files = Dir.glob(test_filter)

		test_files.each do |file|
			@files << file
		end
	end

	def GetFileList()
		return @files
	end

	def GetOutputFile()
		return @output_file
	end

end

if ($0 == __FILE__)
	file_list = FindFiles.new(ARGV)

	file_list.GetFileList().each do |name|
		$stdout.puts(name)
	end
	$stdout.puts("Output File : " + file_list.GetOutputFile())
end
