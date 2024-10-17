
.. zephyr:code-sample:: dmic_dmm
   :name: Digital Microphone (DMIC) with DMA Memory Management (DMM)
   :relevant-api: audio_dmic_interface dmm

   Use DMM to allocate DMIC buffer.

Overview
********

This sample demonstrates how to allocate buffer for DMIC using DMM.

Requirements
************

The device to be used by the sample is specified by defining a devicetree node
label named ``dmic_dev``. The sample has been tested on :ref:`nrf54h20dk_nrf54h20`
(nrf54h20dk/nrf54h20/cpuapp), and provides overlay file for this board.
