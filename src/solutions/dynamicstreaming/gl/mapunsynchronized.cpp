#include "pch.h"

#include "problems/dynamicstreaming.h"
#include "mapunsynchronized.h"
#include "framework/gfx_gl.h"

// --------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------
DynamicStreamingGLMapUnsynchronized::DynamicStreamingGLMapUnsynchronized()
    : mUniformBuffer()
    , mProgram()
    , mVertexBuffer()
{ }

// --------------------------------------------------------------------------------------------------------------------
DynamicStreamingGLMapUnsynchronized::~DynamicStreamingGLMapUnsynchronized()
{ }

// --------------------------------------------------------------------------------------------------------------------
bool DynamicStreamingGLMapUnsynchronized::Init()
{
    // Uniform Buffer
    glGenBuffers(1, &mUniformBuffer);

    // Program
    const char* kUniformNames[] = { "CB0", nullptr };

    mProgram = CreateProgramT("streaming_vb_gl_vs.glsl",
                              "streaming_vb_gl_fs.glsl",
                              kUniformNames, &mUniformLocation);

    if (mProgram == 0) {
        console::warn("Unable to initialize solution '%s', shader compilation/linking failed.", GetName().c_str());
        return false;
    }

    // Dynamic vertex buffer
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, kParticleBufferSize, nullptr, GL_DYNAMIC_DRAW);

    return glGetError() == GL_NO_ERROR;
}

// --------------------------------------------------------------------------------------------------------------------
void DynamicStreamingGLMapUnsynchronized::Render(const std::vector<Vec2>& _vertices)
{
    // Program
    glUseProgram(mProgram);

    // Uniforms
    Constants cb;
    cb.width = 2.0f / mWidth;
    cb.height = -2.0f / mHeight;

    glBindBuffer(GL_UNIFORM_BUFFER, mUniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Constants), &cb, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, mUniformBuffer);

    // Input Layout
    glEnableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vec2), (void*)offsetof(Vec2, x));

    // Rasterizer State
    glDisable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glDisable(GL_SCISSOR_TEST);
    glViewport(0, 0, mWidth, mHeight);

    // Blend State
    glDisable(GL_BLEND);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    // Depth Stencil State
    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);

    for (int i = 0; i < kParticleCount; ++i)
    {
        int vertex_offset = i * kVertsPerParticle;
        int byte_offset = vertex_offset * sizeof(Vec2);
        int partVertSize = kVertsPerParticle * sizeof(Vec2);

        GLbitfield access = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT;
        void* dst = glMapBufferRange(GL_ARRAY_BUFFER, byte_offset, partVertSize, access);
        if (dst)
        {
            memcpy(dst, &_vertices[vertex_offset], partVertSize);
            glUnmapBuffer(GL_ARRAY_BUFFER);
        }

        glDrawArrays(GL_TRIANGLES, vertex_offset, kVertsPerParticle);
    }
}

// --------------------------------------------------------------------------------------------------------------------
void DynamicStreamingGLMapUnsynchronized::Shutdown()
{
    glDeleteBuffers(1, &mVertexBuffer);

    glDeleteBuffers(1, &mUniformBuffer);
    glDeleteProgram(mProgram);
}

