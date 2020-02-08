#include "DrawTriangle.h"

DrawTriangle::DrawTriangle(LPDIRECT3DDEVICE9 d3dDevice)
{
    OutputDebugString(L"DrawTriangle()构造\n");
	p_d3dDevice = d3dDevice;
}

DrawTriangle::~DrawTriangle()
{
    OutputDebugString(L"~DrawTriangle()析构\n");
}

/*+----------------------------------------------------
 *|d3dpp.EnableAutoDepthStencil = TRUE;//自动维护深度缓存
 *|d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//深度缓存像素格式[clear时清除ZBUFFER]
 *|m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);//D3DCLEAR_ZBUFFER清除深度内容
 *|如果开启自动深度维护，则就会启用深度，配合：clear使用 深度清屏 则绘制的点，线，三角形等z值就起作用
 *+----------------------------------------------------
 */
HRESULT DrawTriangle::CreateVectex(float x, float y ,DWORD color)
{

    VertexTriangle Vertices[] =
    {
        { x,  y + 32.0f, 1.0f, 1.0f, color, }, // x, y, z, rhw, color
        { x, y, 1.0f, 1.0f, 0xffffffff, },
        { x + 48.0f, y + 32.0f, 1.0f, 1.0f, color, },
        { x + 48.0f, y, 1.0f, 1.0f, color, },
    };

    // Create the vertex buffer. Here we are allocating enough memory
    // (from the default pool) to hold all our 3 custom Vertices. We also
    // specify the FVF, so the vertex buffer knows what data it contains.
    if (FAILED(p_d3dDevice->CreateVertexBuffer(sizeof(Vertices),0, D3DFVF_TRIANGLE,D3DPOOL_DEFAULT, &g_pVB, NULL)))
    {
        return E_FAIL;
    }

    // Now we fill the vertex buffer. To do this, we need to Lock() the VB to
    // gain access to the Vertices. This mechanism is required becuase vertex
    // buffers may be in device memory.
    VOID* pVertices;
    if (FAILED(g_pVB->Lock(0, sizeof(Vertices), &pVertices, 0)))
        return E_FAIL;
    memcpy(pVertices, Vertices, sizeof(Vertices));
    g_pVB->Unlock();

    return S_OK;
}

HRESULT DrawTriangle::Create3DVectex()
{
    Vertex3DTriangle Vertices[] =
    {
        { -1.0f,-1.0f, 0.0f, 0xffff0000, },
        {  -1.0f, 1.0f, 0.0f, 0xffffffff, },
        {  1.0f,-1.0f, 0.0f, 0xff0000ff, },
        {  1.0f, 1.0f, 0.0f, 0xffffffff, },
    };

    if (FAILED(p_d3dDevice->CreateVertexBuffer(sizeof(Vertices), 0, D3DFVF_3D_TRIANGLE, D3DPOOL_DEFAULT, &g_pVB, NULL)))
    {
        return E_FAIL;
    }

    VOID* pVertices;
    if (FAILED(g_pVB->Lock(0, sizeof(Vertices), &pVertices, 0)))
        return E_FAIL;
    memcpy(pVertices, Vertices, sizeof(Vertices));
    g_pVB->Unlock();

    p_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    p_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

    return S_OK;
}


void DrawTriangle::Draw(float x, float y, DWORD color)
{
    CreateVectex(x,y,color);

    p_d3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(VertexTriangle));
    p_d3dDevice->SetFVF(D3DFVF_TRIANGLE);
    p_d3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void DrawTriangle::Draw3D()
{
    p_d3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(Vertex3DTriangle));
    p_d3dDevice->SetFVF(D3DFVF_3D_TRIANGLE);
    p_d3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
