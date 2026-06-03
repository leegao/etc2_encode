# etc2_encode
Realtime rgba8 -> etc2 (etc1 subset only) encoder as a compute shader

**Original**

![test_hard.png](test_hard.png)

**ETC1 Mode**

![reconstructed_etc1.png](reconstructed_etc1.png)

PSNR: 27.0509
Total time: 0.00008 ms

**ETC2 Mode**

![reconstructed_etc2.png](reconstructed_etc2.png)

PSNR: 29.2100
Total time: 0.11946 ms

**ASTC Fast AABB 1P Mode**

![reconstructed_astc_aabb.png](reconstructed_astc_aabb.png)

PSNR: 26.6621
Total time: 0.00035 ms

**ASTC Full 1P Mode**

![reconstructed_astc_1p.png](reconstructed_astc_1p.png)

PSNR: 32.2536
Total time: 0.09977 ms

**ASTC Full 2P Mode**

![reconstructed_astc_2p.png](reconstructed_astc_2p.png)

PSNR: 34.831
Total time: 0.21391 ms
