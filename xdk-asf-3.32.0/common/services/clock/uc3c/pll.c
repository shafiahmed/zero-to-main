/**
 * \file
 *
 * \brief Chip-specific PLL implementation
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <avr32/io.h>
#include <compiler.h>
#include <pll.h>

void pll_config_write(const struct pll_config *cfg, unsigned int pll_id)
{
	irqflags_t flags;

	Assert(pll_id < NR_PLLS);

	flags = cpu_irq_save();
	AVR32_SCIF.unlock = 0xaa000000 | (AVR32_SCIF_PLL + (4 * pll_id));
	AVR32_SCIF.pll[pll_id] = cfg->ctrl;
	cpu_irq_restore(flags);
}

void pll_enable(const struct pll_config *cfg, unsigned int pll_id)
{
	irqflags_t flags;

	Assert(pll_id < NR_PLLS);

	flags = cpu_irq_save();
	AVR32_SCIF.unlock = 0xaa000000 | (AVR32_SCIF_PLL + (4 * pll_id));
	AVR32_SCIF.pll[pll_id] = cfg->ctrl | (1U << AVR32_SCIF_PLLEN);
	cpu_irq_restore(flags);
}

void pll_disable(unsigned int pll_id)
{
	irqflags_t flags;

	Assert(pll_id < NR_PLLS);

	flags = cpu_irq_save();
	AVR32_SCIF.unlock = 0xaa000000 | (AVR32_SCIF_PLL + (4 * pll_id));
	AVR32_SCIF.pll[pll_id] = 0;
	cpu_irq_restore(flags);
}
