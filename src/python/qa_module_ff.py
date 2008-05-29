#!/usr/bin/env python

from gnuradio import gr, gr_unittest
import dab_swig

class qa_modulo_ff(gr_unittest.TestCase):
	"""
	@brief Module test for the moving sum class.

	This class implements a test bench to verify the corresponding C++ class.
	"""

	def setUp(self):
		self.tb = gr.top_block()

	def tearDown(self):
		self.tb = None

	def test_001_modulo_ff(self):
		div = 17.7313
		src_data = range(-1000,1000)
		src_data = [float(x) / float(7) for x in src_data]
		expected_result = [x % div for x in src_data]
		src = gr.vector_source_f(src_data)
		modulo = dab_swig.modulo_ff(div)
		dst = gr.vector_sink_f()
		self.tb.connect(src, modulo, dst)
		self.tb.run()
		result_data = dst.data()
		self.assertFloatTuplesAlmostEqual(expected_result, result_data, 4)

if __name__ == '__main__':
	gr_unittest.main()

