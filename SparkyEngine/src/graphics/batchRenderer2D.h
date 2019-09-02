#pragma once 

#include "renderable2d.h"
#include <cstddef>

namespace core {
	namespace graphics {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define ATTRIB_VERTEX_INDEX	0
#define ATTRIB_COLOR_INDEX	1

		class BatchRenderer2D : public Renderer2D
		{
		private:
			unsigned int m_VAO;
			unsigned int m_VBO;
			IndexBuffer *m_IBO;

			unsigned int m_IndicesCount;
			VertexData *m_BufferData;
			
		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void begin() override;
			void end() override;
			void submit(const Renderable2D *renderable) override;
			void flush() override;

		private:
			void init();
		};

	}

}