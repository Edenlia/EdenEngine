//
// Created by 章书飏 on 2025/4/18.
//

#ifndef EDENENGINE_IRHI_H
#define EDENENGINE_IRHI_H

namespace EE {

    class IRHIDevice;
    class IRHISwapChain;
    class IRHICommandBuffer;
    class IRHICommandQueue;
    class IRHIPipeline;

    class IRHIContext {
    public:
        virtual ~IRHIContext() = default;

        virtual void Initialize() = 0;
        virtual void Shutdown() = 0;

    };

    class IRHIDevice {

    };

    class IRHISwapChain {

    };

    class IRHICommandBuffer {

    };

    class IRHICommandQueue {

    };

    class IRHIPipeline {

    };


} // EE

#endif //EDENENGINE_IRHI_H
