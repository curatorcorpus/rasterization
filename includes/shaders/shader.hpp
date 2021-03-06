#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

/*
	External Libraries.
*/
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader {

protected:

	GLuint prog_id;
	GLuint mvp_id;
	GLuint m_id;
	GLuint v_id;
	GLuint p_id;
	GLuint cam_pos_id;

	void 		bind_attrib_loc();
	GLuint      compile(std::string& file_name, const char* code);
	std::string open_file(std::string& shader_path);
	GLuint 		link_shaders(GLuint& vert_id, GLuint& frag_id);
	
	virtual void setup(std::string& vert, std::string& frag);

public:

	Shader();
	Shader(std::string shader_path);
	~Shader();

	void bind();
	void unbind();
	void update_cam_pos(glm::vec3 position);
	void update_view_matrix(glm::mat4& v);
	void update_matrices(glm::mat4& m, glm::mat4& v);
	void update_matrices(glm::mat4& m, glm::mat4& v, glm::mat4& mvp);
	void update_mvp(glm::mat4& mvp);
	GLuint get_prog_id();

	void set_proj_matrix(glm::mat4& p);
};


#endif