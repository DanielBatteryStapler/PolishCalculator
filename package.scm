(use-modules (guix packages)
	(guix gexp)
	((guix licenses) #:prefix license:)
	(guix build-system meson)
	(gnu packages pkg-config)
	(gnu packages cmake)
	(gnu packages ncurses))

(package
	(name "PolishCalculator")
	(version "0.0")
	(inputs
		`(("ncurses" ,ncurses)))
	(native-inputs 
		`(("pkg-config" ,pkg-config)
		("cmake" ,cmake)))
	(propagated-inputs '())
	(source (local-file "./src" #:recursive? #t))
	(build-system meson-build-system)
	(synopsis "PolishCalculator: command-line calculator")
	(description
		"Command-line calculator that uses polish-notation")
	(home-page "https://github.com/danielbatterystapler/PolishCalculator")
	(license license:gpl2+))

