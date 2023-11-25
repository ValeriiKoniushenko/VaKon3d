// MIT License
//
// Copyright (c) 2023 Valerii Koniushenko
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "Widget.h"

#include "ShaderPack.h"
#include "Texture.h"
#include "Window.h"
#include "glm/ext/matrix_clip_space.hpp"

void Widget::setTexture(Texture& texture)
{
	texture_ = &texture;
	isDirtyTexture_ = true;
}

Texture* Widget::getTexture()
{
	return texture_;
}

const Texture* Widget::getTexture() const
{
	return texture_;
}

void Widget::resetTexture()
{
	texture_ = nullptr;
}

void Widget::draw(ShaderPack& shaderPack)
{
	auto& shader = shaderPack["widget"];
	shader.use();

	if (texture_)
	{
		texture_->bind();
		if (isDirtyTexture_)
		{
			texture_->loadToGpu();
			isDirtyTexture_ = false;
		}
	}
	if (!vao_.isGenerated())
	{
		vao_.generate();
	}
	if (!vbo_.isGenerated())
	{
		vbo_.generate();
	}

	vao_.bind();

	if (isDirtyVertices_)
	{
		auto vertices = verticesTemplate_;
		vertices[1].position.x *= size_.width;
		vertices[2].position.x *= size_.width;
		vertices[2].position.y *= size_.height;
		vertices[4].position.x *= size_.width;
		vertices[4].position.y *= size_.height;
		vertices[5].position.y *= size_.height;

		vbo_.bind();
		vbo_.data(vertices);
		isDirtyVertices_ = false;
	}

	Gl::Vao::vertexAttribPointer(1, 2, Gl::Type::Float, false, 4 * sizeof(float), nullptr);
	Gl::Vao::vertexAttribPointer(2, 2, Gl::Type::Float, false, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));

	static glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(GetWindow().getSize().width), 0.0f,
		static_cast<float>(GetWindow().getSize().height), 0.1f, 1000.0f);
	
	shader.uniform("uProjection", false, proj);

	Gl::drawArrays(GL_TRIANGLES, 0, verticesTemplate_.size());
}

void Widget::setSize(Utils::FSize2D size)
{
	size_ = size;
	isDirtyVertices_ = true;
}

Utils::FSize2D Widget::getSize() const
{
	return size_;
}
