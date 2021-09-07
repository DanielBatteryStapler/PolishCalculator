project('PolishCalculator', 'cpp')

add_project_arguments([
		
	], language: 'cpp')
add_project_link_arguments([
		
	], language: 'cpp')

dep = [
	dependency('ncurses')
]

inc = [
	'.'
]

src = [
	'main.cpp',
	'Fraction.cpp',
	'Operator.cpp',
	'UniNum.cpp'
]

executable(
	'calc',
	sources : src,
	dependencies : dep,
	include_directories : inc,
	install : true,
	override_options : ['cpp_std=c++11']
)

