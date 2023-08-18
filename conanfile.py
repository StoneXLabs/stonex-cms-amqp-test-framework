from conans import ConanFile, CMake, tools

def get_verion_tag():
    git = tools.Git("stonex-cms-amqp-test-framework")
    try:
        return "%s" % (git.get_tag())
    except Exception as e:
        return e

class StonexCmsAmqpTestFrameworkConan(ConanFile):
    name = "stonex-cms-amqp-test-framework"
    version = get_verion_tag()
    license = "<Put the package license here>"
    author = "krzysztof.obrebski@stonex.com"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "cms client interoperability test"
    topics = ("cms","amqp")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "cmake"

    def requirements(self):
       	self.requires("stonex-cms-amqp-test-engine/None@enterprise_messaging/test")
        if self.settings.os == "Windows":
           self.requires("stonex-logger-wrapper/0.0.2@enterprise_messaging/test")
           self.requires("stonex-cms-amqp-lib/None@enterprise_messaging/test")
           self.requires("protobuf/3.20.1@enterprise_messaging/test")
           self.requires("fmt/9.1.0@enterprise_messaging/test")
           self.requires("boost/1.78.0@enterprise_messaging/stable")
        if self.settings.os == "Linux":
           self.requires("protobuf/3.20.0")
           self.requires("boost/1.78.0")
        
    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC
        if self.settings.arch == "x86":
            self.options["protobuf"].use_32_time_t = True

    def source(self):
         self.run("git clone https://github.com/StoneXLabs/stonex-cms-amqp-test-framework.git")  

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include",src="stonex-cms-amqp-test-framework-lib/include")
        self.copy("*.lib", dst="lib",src="lib", keep_path=False)
        self.copy("*.pdb", dst="lib",src="lib", keep_path=False)
        self.copy("*.so*", dst="lib",src="lib", keep_path=False)
        self.copy("*.a", dst="lib",src="lib", keep_path=False)
        
        self.copy("*.exe", dst="bin",src="bin", keep_path=False)
        
        self.copy("*.config", dst="bin",src="Test")
        
        self.copy("*message*.txt", dst="bin",src="Test")

    def package_info(self):
        self.cpp_info.libs = self.collect_libs()

