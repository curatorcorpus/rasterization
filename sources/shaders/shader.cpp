#include <shader.hpp>

/*
	Assumes shader names will be the same for both frag and vert shaders.
*/
Shader::Shader(std::string shader_path) {

	// relative local path to shader res.
	std::string loc_res_path = "../resources/shaders/";

	std::string vert_shader_path = loc_res_path + shader_path + ".vert";
	std::string frag_shader_path = loc_res_path + shader_path + ".frag";

	setup(vert_shader_path, frag_shader_path);
}

Shader::~Shader() {
	glDeleteProgram(prog_id);
}

void Shader::setup(std::string& vert_path, std::string& frag_path) {

	// read in shader files.
	std::string vert_shader_code = open_file(vert_path);
	std::string frag_shader_code = open_file(frag_path);

	// compile shader programs.
	GLuint vert_id = compile(vert_path, vert_shader_code.c_str());
	GLuint frag_id = compile(frag_path, frag_shader_code.c_str());

	// compiled shaders to program
	this->prog_id = link_shaders(vert_id, frag_id);
	bind(prog_id);
}

std::string Shader::open_file(std::string& shader_path) {

	// read shader file code.
	std::string code = "";
	std::ifstream shader_stream(shader_path.c_str(), std::ios::in);
	if(shader_stream.is_open()) {
		std::string line = "";
		
		while(getline(shader_stream, line))
		{
			code += "\n" + line;
		}
		shader_stream.close();
	
	} else {
		std::cerr << "[DEBUG::SHADER_CPP] Shader Failed to load! Wrong path?" << std::endl;
	}

	return code;
}

GLuint Shader::compile(std::string& file_name, const char* code) {

	std::cerr << "[DEBUG::SHADER_CPP] Compiling Shader: " << file_name << std::endl;

	// create empty shader object. [only limited to vert and frag shader]
	// determines which shader processor should be used for the provided code.
	GLuint shader_id;
	if(file_name.find("vert") != std::string::npos) {
						std::cerr << "working" << std::endl;
		shader_id = glCreateShader(GL_VERTEX_SHADER);
	} else {
		shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	}

	glShaderSource(shader_id, 1, &code, NULL); // attach source code to empty shader object.
	glCompileShader(shader_id);				   // compile

	GLint result = GL_FALSE;
	GLint info_log_length;

	// check if shader programs compiled.
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	std::cerr << result << std::endl;
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

	if(info_log_length > 0) {
		std::vector<char> err_msg(info_log_length + 1);
		glGetShaderInfoLog(shader_id, info_log_length, NULL, &err_msg[0]);

		std::cerr << "[DEBUG::SHADER_CPP] " << &err_msg << std::endl;
		std::cerr << "[DEBUG::SHADER_CPP] Shader Compilation Failed!" << std::endl;
	}
		std::cerr << "working" << std::endl;
	return shader_id;
}

GLuint Shader::link_shaders(GLuint& vert_id, GLuint& frag_id) {

	std::cerr << "[DEBUG::SHADER_CPP] Linking shader program" << std::endl;

	// create program object.
	GLuint program = glCreateProgram();
	glAttachShader(program, vert_id);
	glAttachShader(program, frag_id);
	glLinkProgram(program);

	// check program is running
	GLint result = GL_FALSE;
	GLint info_log_length;
	if(info_log_length > 0) {
		std::vector<char> err_msg(info_log_length + 1);
		glGetProgramInfoLog(program, info_log_length, NULL, &err_msg[0]);

		std::cerr << "[DEBUG::SHADER_CPP] " << &err_msg << std::endl;
		std::cerr << "[DEBUG::SHADER_CPP] Program Linking Failed!" << std::endl;
	}

	// detach shader object from program
	glDetachShader(program, vert_id);
	glDetachShader(program, frag_id);

	// free shader object memory.
	glDeleteShader(vert_id);
	glDeleteShader(vert_id);

	return program;
}

void Shader::bind(GLuint& program) {
	glUseProgram(program);
}