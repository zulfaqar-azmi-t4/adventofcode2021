from conans import ConanFile

class ConanPackage(ConanFile):
    name = 'adventofcode'
    version = '0.1.0'

    generators = 'cmake_find_package'

    requires = [
        ('fmt/8.0.1'),
        ('dataframe/1.19.0'),
    ]

    default_options = (
    )
