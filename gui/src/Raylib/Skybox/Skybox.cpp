/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ShaderEnc
*/

#include "Skybox.hh"

Raylib::Skybox::Skybox(const std::string &texturePath, const std::string &skyboxVsFile,
	const std::string &skyboxFsFile, const std::string &cubemapVsFile, const std::string &cubemapFsFile):
		_skybox("", "")
{
	initSkybox(texturePath, skyboxVsFile, skyboxFsFile, cubemapVsFile, cubemapFsFile);
}

Raylib::Skybox::~Skybox()
{
}

Shader Raylib::Skybox::getShader() const
{
	return _shader;
}

Raylib::Model3D Raylib::Skybox::getSkybox() const
{
	return _skybox;
}

void Raylib::Skybox::Draw() const
{
	RaylibGL::myRlDisableBackfaceCulling();
	RaylibGL::myRlDisableDepthMask();
	DrawModel(_skybox.getModel(), (Vector3){0, 0, 0}, 1.0f, WHITE);
	RaylibGL::myRlEnableBackfaceCulling();
	RaylibGL::myRlEnableDepthMask();
}

extern "C" {
	void Raylib::Skybox::initSkybox(const std::string &texturePath, const std::string &skyboxVsFile,
	    const std::string &skyboxFsFile, const std::string &cubemapVsFile, const std::string &cubemapFsFile)
	{
		Mesh cube = GenMeshCube(1.0f, 1.0f, 1.0f);
    	_skybox.setModel(LoadModelFromMesh(cube));

		_skybox.getModel().materials[0].shader = LoadShader(TextFormat(skyboxVsFile.c_str(), 330),
                                            TextFormat(skyboxFsFile.c_str(), 330));

		SetShaderValue(_skybox.getModel().materials[0].shader, GetShaderLocation(_skybox.getModel().materials[0].shader, "environmentMap"), (int[1]){ MATERIAL_MAP_CUBEMAP }, SHADER_UNIFORM_INT);
		SetShaderValue(_skybox.getModel().materials[0].shader, GetShaderLocation(_skybox.getModel().materials[0].shader, "doGamma"), (int[1]) { 1 }, SHADER_UNIFORM_INT);
		SetShaderValue(_skybox.getModel().materials[0].shader, GetShaderLocation(_skybox.getModel().materials[0].shader, "vflipped"), (int[1]){ 1 }, SHADER_UNIFORM_INT);
		_shader = LoadShader(TextFormat(cubemapVsFile.c_str(), 330),
                            TextFormat(cubemapFsFile.c_str(), 330));

    	SetShaderValue(_shader, GetShaderLocation(_shader, "environmentMap"), (int[1]){ 0 }, SHADER_UNIFORM_INT);

		Texture2D panorama = LoadTexture(texturePath.c_str());

		_skybox.getModel().materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = RaylibGL::genTextureCubemap(_shader, panorama, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	}
}
