#include <string>
#include <filesystem>

#include <unistd.h>
#include <sys/wait.h>

const std::string[] other_modules = {
	"ucd_snmp", "libxml", "rapidjson", "dd_odbc", "jsonc", "libcurl", "CTSLicense", "gdbm", "hposmail", "openssl", "termcap", "readline", "sqlite", "bzip2", "zlib", "python", "libffi", "pkgconfig", "OMOracle", "libtiff", "datadirect_jdbcdriver", "oracle_lib", "berkeleydb", "lib_ssh2", "solr", "mod_jk", "idol", "apache", "perl", "gettext", "glib", "gmime", "expect", "mysql", "gs"
};

const std::string[] os_modules = {
	"om_pkg_os", "omux", "sap_rfcsdk", "configuration", "otostemplates", "os_msg", "os", "od_msg", "odcommon", "rds", "sap_msg", "erp", "os_xform", "ens", "os_jni", "os_web_common", "os_model", "sap_scps_gw", "sap_scps", "os_ippg", "omwc", "os_wsg", "sa_service", "sa_km", "sa_kyocera", "sa_web_ui", "sa_web", "sa_hpoxpd", "RightFax", "dialogic_wrapper", "sa_ricoh_android", "sa_ricoh", "OTOSCallback", "odman_ui", "odman_wsg", "om_migration", "osm_web_ui", "jm_web_ui", "os_rest_wsg", "otos_web_api_gw", "otos_ws_registry", "os_pkg", "opensource_pkg"
}

const std::string buildFolder = "/eng/build/linux514_x86_64";
const std::string gitRepository = "https://{}:{}@gitlab.otxlab.net/otom-workflow/{}.git";

std::string getEnvironmentVariable(const std::string& variable) {
	int i = 0;
	while(environ[i]) {
		std::string envVar { environ[i++] };
		std::cout << "environ[" << i << "] = " << envVar << std::endl;
	}
}

void gitCloneModule(const std::string& module) {
	const std::string modulePath = buildFolder + "/" + module;
	if (std::filesystem::exists({modulePath})) {
		std::cout << modulePath << " already exists..." << std::endl;
		return;
	}
	std::cout << "parent process before forking, pid = " << static_cast<int>getpid() << std::endl;
	int rc = fork();
	if (rc < 0) {
		std::cerr << "Unable to fork!" << std::endl;
		exit(1);
	}
	if (rc == 0) {
		// child process
		std::cout << "child process before exec, pid = " << static_cast<int>getpid() << " parent pid = " << static_cast<int>getppid() << std::endl;
		char *prog = "git";
		char *repositoryURL = 
		char **argv = {"git", "clone", }
	} else {
		int childPid = wait();
		std::cout << "Done waiting for child with pid = " << childPid << std::endl;
	}
}