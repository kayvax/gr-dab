/* -*- c++ -*- */
/*
 * Copyright 2004 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */
#ifndef INCLUDED_DAB_FREQUENCY_INTERLEAVER_VCC_H
#define INCLUDED_DAB_FREQUENCY_INTERLEAVER_VCC_H

#include <gr_sync_block.h>

class dab_frequency_interleaver_vcc;

/*
 * We use boost::shared_ptr's instead of raw pointers for all access
 * to gr_blocks (and many other data structures).  The shared_ptr gets
 * us transparent reference counting, which greatly simplifies storage
 * management issues.  This is especially helpful in our hybrid
 * C++ / Python system.
 *
 * See http://www.boost.org/libs/smart_ptr/smart_ptr.htm
 *
 * As a convention, the _sptr suffix indicates a boost::shared_ptr
 */
typedef boost::shared_ptr<dab_frequency_interleaver_vcc> dab_frequency_interleaver_vcc_sptr;

/*!
 * \brief Return a shared_ptr to a new instance of dab_frequency_interleaver_vcc.
 *
 * To avoid accidental use of raw pointers, dab_frequency_interleaver_vcc's
 * constructor is private.  dab_make_frequency_interleaver_vcc is the public
 * interface for creating new instances.
 */
dab_frequency_interleaver_vcc_sptr 
dab_make_frequency_interleaver_vcc (const std::vector<short> &interleaving_sequence);

/*!
 * \brief Interleaves vector elements according to the interleaving sequence: out[sequence[i]] = in[i]
 * \ingroup DAB
 * 
 * \param sequence interleaving sequence
 */
class dab_frequency_interleaver_vcc : public gr_sync_block
{
	private:
		// The friend declaration allows dab_make_frequency_interleaver_vcc to
		// access the private constructor.

		friend dab_frequency_interleaver_vcc_sptr
    dab_make_frequency_interleaver_vcc (const std::vector<short> &interleaving_sequence);

		dab_frequency_interleaver_vcc (const std::vector<short> &interleaving_sequence);  	// private constructor

    std::vector<short> d_interleaving_sequence;
		unsigned int d_length;

	public:
    void set_sequence(const std::vector<short> &interleaving_sequence) { d_interleaving_sequence = interleaving_sequence; }
		int work (int noutput_items,
		          gr_vector_const_void_star &input_items,
		          gr_vector_void_star &output_items);
};

#endif /* INCLUDED_DAB_FREQUENCY_INTERLEAVER_VCC_H */