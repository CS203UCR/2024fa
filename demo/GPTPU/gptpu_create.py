#https://www.tensorflow.org/lite/models/convert/convert_models#convert_concrete_functions_
import numpy as np
import tensorflow as tf
import time
from pycoral.adapters import classify
from pycoral.adapters import common
from pycoral.utils.dataset import read_label_file
from pycoral.utils.edgetpu import make_interpreter 

class GEMM(tf.Module):
    @tf.function(input_signature=[tf.TensorSpec(shape=(8192), dtype=tf.float32)])
    def __call__(self, input):
        a = input[0:4096]
        b = input[4096:8192]
        a = tf.reshape(a, [64,64])
        b = tf.reshape(b, [64,64])
        c = tf.linalg.matmul(a,b)
        return c
    
def gemm(input):
    a = tf.constant(input[0:16], dtype=tf.float32)
    a = tf.reshape(a, [4,4])
    b = tf.constant(input[16:24], dtype=tf.float32)
    b = tf.reshape(b, [4,2])
    c = tf.linalg.matmul(a,b)
    divisor = 2.0
    c = tf.math.divide_no_nan(c,divisor)
    c = tf.reshape(c, [8])
    c = tf.cast(c, tf.uint8)
    result = 0
    for x in range(8):
        result = result * 2 + c[x]
    return result

def main():
    # Convert the model
    model = GEMM()
    concrete_func = model.__call__.get_concrete_function()
    converter = tf.lite.TFLiteConverter.from_concrete_functions([concrete_func],model)
    tflite_model = converter.convert()
    # Save the model.
    with open('gemm_gptpu.tflite', 'wb') as f:
      f.write(tflite_model)
    # Load the model
    interpreter = make_interpreter("gemm_gptpu.tflite")
    interpreter.allocate_tensors()
    input_details = interpreter.get_input_details()
    output_details = interpreter.get_output_details()
    # End loading the model
    np.random.seed(10)
    for x in range(5):
        a = np.random.randint(2,size=4096)
        b = np.random.randint(2,size=4096)
        input = np.append(a,b)
        a = np.reshape(a, (64,64))
        b = np.reshape(b, (64,64))
    # Run np_matmul
        start = time.perf_counter()
        c = np.matmul(a,b)
        execution_time = time.perf_counter() - start
        print('CPU: %.2f us' % (execution_time*1000000))
    # End np_matmul
    # Run inference
        start = time.perf_counter()
        interpreter.set_tensor(input_details[0]['index'], input.astype('float32'))
        interpreter.invoke()
        result = interpreter.get_tensor(output_details[0]['index'])
        inference_time = time.perf_counter() - start
    # End inference
        print('Edge TPU: %.2f us' % (inference_time*1000000))
        print("Results consistent? " + str(np.array_equal(c.astype('float32'), result)))

if __name__ == '__main__':
  main()