#include "TestTexture2D.h"

namespace Test
{
	TestTexture2D::TestTexture2D()
        :translationa({200, 200, 0}), translationb({400, 400, 0})
	{
        float positions[] =
        {
             -50.f, -50.0f, 0.0f, 0.0f,
              50.f, -50.0f, 1.0f, 0.0f,
              50.f,  50.0f, 1.0f, 1.0f,
             -50.f,  50.0f, 0.0f, 1.0f

        };

        unsigned int indicies[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        shader = std::make_unique<Shader>("res/shaders/Basic.Shader");
        ibo = std::make_unique<IndexBuffer>(indicies, 6);
        vao = std::make_unique<VertexArray>();
        texture = std::make_unique<Texture>("res/textures/DefaultTexture.png");

      
        vbo = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        vao->AddBuffer(*vbo, layout);

      

        proj = glm::ortho(0.f, 960.f, 0.f, 540.f, -1.f, 1.f);
        view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        shader->Bind();

       
        texture->Bind();
        shader->SetUniform1i("u_Texture", 0);

      

        bool one = true;
        glm::vec3 translationa(200, 200, 0);
        glm::vec3 translationb(400, 400, 0);
	}

	void TestTexture2D::Update(float deltaTime)
	{
	}

	void TestTexture2D::Render()
	{

        ImGui::SliderFloat2("Translation A", &translationa.x, 0.0f, 960.0f);
        ImGui::SliderFloat2("Translation B", &translationb.x, 0.0f, 960.0f);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        Renderer renderer;

        {
            shader->Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationa);
            glm::mat4 MVP = proj * view * model;
            shader->SetUniformMat4f("u_MVP", MVP);
            renderer.Draw(*vao, *ibo, *shader);
        }

        {
            shader->Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationb);
            glm::mat4 MVP = proj * view * model;
            shader->SetUniformMat4f("u_MVP", MVP);
            renderer.Draw(*vao, *ibo, *shader);
        }
	}

	void TestTexture2D::IMGUIRender()
	{
        ImGui::SliderFloat2("float", &translationa.x, 0.0f, 960.0f);
        ImGui::SliderFloat2("float1", &translationb.x, 0.0f, 960.0f);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	TestTexture2D::~TestTexture2D()
	{
		
	}
}