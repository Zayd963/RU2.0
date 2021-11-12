#include "TestTexture2D.h"

namespace Test
{
	TestTexture2D::TestTexture2D()
        :translationa({0, 0, 0}), translationb({400, 400, 0})
	{
        float positions[] =
        {
             -50.f, -50.0f, 50.0f, 0.0f, 0.0f,
              50.f, -50.0f, 50.0f, 1.0f, 0.0f,
              50.f,  50.0f, 50.0f, 1.0f, 1.0f,
             -50.f,  50.0f, 50.0f, 0.0f, 1.0f

        };

        unsigned int indicies[] =
        {
            0, 1, 2,
            2, 3, 0,
            
        };

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        shader = std::make_unique<Shader>("res/shaders/Basic.Shader");
        ibo = std::make_unique<IndexBuffer>(indicies, 6);
        vao = std::make_unique<VertexArray>();
        texture = std::make_unique<Texture>("res/textures/DefaultTexture.png");

      
        vbo = std::make_unique<VertexBuffer>(positions, 5 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        vao->AddBuffer(*vbo, layout);

      

        proj = glm::perspective(45.f, 4.f / 3.f, 0.f, 100.f);
        view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        shader->Bind();

       
        texture->Bind();
        shader->SetUniform1i("u_Texture", 0);

      

      
	}

	void TestTexture2D::Update(float deltaTime)
	{
	}

	void TestTexture2D::Render()
	{

 

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
        ImGui::SliderFloat3("Translation A", &translationa.x, -1000, 1.f);
        ImGui::SliderFloat3("Translation B", &translationb.x, -1000.f, 1.f);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	TestTexture2D::~TestTexture2D()
	{
		
	}
}