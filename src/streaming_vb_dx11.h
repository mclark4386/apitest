#pragma once

#include "gfx_dx11.h"

class StreamingVB_DX11 : public StreamingVB
{
public:
    StreamingVB_DX11();
    virtual ~StreamingVB_DX11();

    virtual bool Init() override;

    virtual bool Begin(GfxBaseApi* _activeAPI) override;

    virtual void Draw(VertexPos2* vertices, int count) override;

private:
    struct Constants
    {
        float width;
        float height;
        float pad[2];
    };

    ID3D11InputLayout* m_layout;
    ID3D11Buffer* m_cb;
    ID3D11VertexShader* m_vs;
    ID3D11PixelShader* m_ps;
    ID3D11SamplerState* m_sampler;
    ID3D11RasterizerState* m_rs;
    ID3D11BlendState* m_bs;
    ID3D11DepthStencilState* m_dss;

    ID3D11Buffer* m_dyn_vb;
    int m_dyn_offset;
};
