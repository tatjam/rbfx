//
// Copyright (c) 2008-2020 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include <EASTL/unique_ptr.h>

#include "../Core/Object.h"
#include "../Graphics/GPUObject.h"
#include "../Graphics/GraphicsDefs.h"

namespace Urho3D
{

/// Hardware constant buffer.
class URHO3D_API ConstantBuffer : public Object, public GPUObject
{
    URHO3D_OBJECT(ConstantBuffer, Object);

    using GPUObject::GetGraphics;

public:
    /// Construct.
    explicit ConstantBuffer(Context* context);
    /// Destruct.
    ~ConstantBuffer() override;

    /// Register object with the engine.
    static void RegisterObject(Context* context);

    /// Recreate the GPU resource and restore data if applicable.
    void OnDeviceReset() override;
    /// Release the buffer.
    void Release() override;

    /// Set size and create GPU-side buffer. Return true on success.
    bool SetSize(unsigned size);
    /// Set a generic parameter and mark buffer dirty.
    void SetParameter(unsigned offset, unsigned size, const void* data);
    /// Set a Vector3 array parameter and mark buffer dirty.
    void SetVector3ArrayParameter(unsigned offset, unsigned rows, const void* data);
    /// Apply to GPU.
    void Apply();
    /// Set data to GPU directly.
    void SetGPUData(const void* data);

    /// Return size.
    unsigned GetSize() const { return size_; }

    /// Return whether has unapplied data.
    bool IsDirty() const { return dirty_; }

private:
    /// Shadow data.
    ea::unique_ptr<unsigned char[]> shadowData_;
    /// Buffer byte size.
    unsigned size_{};
    /// Dirty flag.
    bool dirty_{};
};

}
