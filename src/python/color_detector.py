"""*L///////////////////////////////////////////////////////////////////////////////////////
Copyright (c) 2019, Luis Tobias, Sidibe Desire, France
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

  Neither the name of the Authors nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
"""

import cv2
import numpy as np
import matplotlib.pyplot as plt


class ColorSegmentation():
    def __init__(self, cov_, mean_, threshold):
        self.mean = mean_
        self.cov = cov_
        self.inv_cov = cv2.invert(cov_)[1]
        self.th = threshold

    def normalize_rbg(self, image):
        np.seterr(divide='ignore', invalid='ignore')
        image = image.astype(np.float)
        normalized = np.zeros(image.shape, dtype=np.float)
        summed = np.sum(image, axis=2)
        normalized[:, :, 0] = image[:, :, 0] / summed
        normalized[:, :, 1] = image[:, :, 1] / summed
        normalized[:, :, 2] = image[:, :, 2] / summed
        return normalized

    def get_color_mask(self, image):
        ng = image[:, :, 1] - self.mean[1]
        nr = image[:, :, 2] - self.mean[0]
        gate = -0.5 * ((nr*nr * self.inv_cov[0, 0])
                       + (2*self.inv_cov[0, 1] * nr*ng)
                       + (ng*ng * self.inv_cov[1, 1]))
        gate = np.exp(gate)
        _, mask = cv2.threshold(gate, self.th, 1, cv2.THRESH_BINARY)
        return mask.astype(np.uint8)


covariance = np.array([[0.0038, -0.0009], [-0.0009, 0.0009]])
mean = np.array([0.4404, 0.3111])
th = 0.33

# img = cv2.imread("/home/luis/Pictures/person.jpeg", -1)
# img = cv2.imread("/home/luis/Pictures/people.jpg", -1)
img = cv2.imread("/home/luis/Pictures/person2.jpg", -1)

convertor = ColorSegmentation(covariance, mean, th)

normal_bgr = convertor.normalize_rbg(img)
mask = convertor.get_color_mask(normal_bgr)

img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
plt.imshow(img * mask[:, :, None])
plt.show()
