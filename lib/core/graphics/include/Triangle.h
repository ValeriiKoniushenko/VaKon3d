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

#pragma once

#include "Size.h"
#include "TriangleVbo.h"
#include "Vao.h"

class Texture;
class ShaderPack;

class Triangle
{
public:
	Triangle() = default;
	explicit Triangle(Texture& texture);

	void draw(ShaderPack& shaderPack);

	void setTexture(Texture& texture);
	[[nodiscard]] Texture* getTexture();
	[[nodiscard]] const Texture* getTexture() const;
	void resetTexture();

	void setSize(Utils::FSize2D size);
	[[nodiscard]] Utils::FSize2D getSize() const;

	void setPosition(glm::vec3 position);
	void move(glm::vec3 offset);
	[[nodiscard]] glm::vec3 getPosition() const;

	void setRotate(float degrees);
	[[nodiscard]] float getRotate() const;
	void rotate(float degrees);

	void setOrigin(glm::vec3 origin);
	[[nodiscard]] glm::vec3 getOrigin() const;

private:
	Texture* texture_ = nullptr;
	Vao vao_;
	TriangleVbo vbo_;
	Utils::FSize2D size_ = {100.f, 100.f};
	glm::vec3 position_{};
	glm::vec3 origin_{};
	float rotate_{};
	bool isDirtyVertices_ = true;
	bool isDirtyTexture_ = true;

	// clang-format off
	const inline static std::vector<TriangleVbo::Unit> verticesTemplate_ = {
		{ {0.f, 0.f, 0.f}, {0.f, 0.f}, {0.f, 0.f, 1.f} },
		{ {1.f, 0.f, 0.f}, {1.f, 0.f}, {0.f, 0.f, 1.f} },
		{ {1.f, 1.f, 0.f}, {1.f, 1.f}, {1.f, 0.f, 1.f} }
	};
	// clang-format on
};