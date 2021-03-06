#pragma once

#include "solutions/untexturedobjectssoln.h"

// --------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------
class UntexturedObjectsGLTexCoord : public UntexturedObjectsSolution
{
public:
    UntexturedObjectsGLTexCoord();
    virtual ~UntexturedObjectsGLTexCoord() { }

    virtual bool Init(const std::vector<UntexturedObjectsProblem::Vertex>& _vertices,
                      const std::vector<UntexturedObjectsProblem::Index>& _indices,
                      size_t _objectCount) override;

    virtual void Render(const std::vector<Matrix>& _transforms);
    virtual void Shutdown();

    // The name of this solution.
    virtual std::string GetName() const { return "UntexturedObjectsGLTexCoord"; }

private:
    GLuint m_ib;
    GLuint m_vb;
    GLuint m_prog;

    struct UniformLocations {
        GLuint ViewProjection;
        UniformLocations() { memset(this, 0, sizeof(*this)); }
    } mUniformLocation;
};
