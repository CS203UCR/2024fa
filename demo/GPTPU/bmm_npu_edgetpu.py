import numpy as np
import tensorflow as tf
import time
from pycoral.adapters import classify
from pycoral.adapters import common
from pycoral.utils.dataset import read_label_file
from pycoral.utils.edgetpu import make_interpreter 

def main():
#    interpreter = tf.lite.Interpreter(model_path="igemm_npu.tflite")
    interpreter = make_interpreter("igemm_npu.tflite")
    interpreter.allocate_tensors()
    input_details = interpreter.get_input_details()
    output_details = interpreter.get_output_details()
# Run inference
    print('----INFERENCE TIME----')
    print('Note: The first inference on Edge TPU is slow because it includes',
            'loading the model into Edge TPU memory.')
    input_data = []
    output_data = []
    np.random.seed(10)
    for x in range(5):
        a = np.random.randint(2,size=16)
        b = np.random.randint(2,size=8)
        input_data = np.append(input_data,np.append(a,b))
    input_data = np.uint8(np.reshape(input_data,(5,24)))
    
    for x in range(5):
        start = time.perf_counter()
#        print(input_data[x])
        interpreter.set_tensor(input_details[0]['index'], np.reshape(input_data[x],(1,24)))
        interpreter.invoke()
        output_data = np.append(output_data, interpreter.get_tensor(output_details[0]['index']))
#        print(output_data[x].astype(np.int32))
        inference_time = time.perf_counter() - start
        print('%.2f us' % (inference_time*1000000))
    print(output_data.astype(np.uint8))
    
if __name__ == '__main__':
  main()