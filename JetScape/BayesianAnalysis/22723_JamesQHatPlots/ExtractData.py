import pickle
import numpy as np

with open('result.pkl', 'rb') as f:
   result_dict = pickle.load(f)

   TResult = np.concatenate(([result_dict['T_array']], [result_dict['T_qhat_truth']], [result_dict['T_qhat_mean']],
      [result_dict['T_credible_up']], [result_dict['T_credible_low']],
      [result_dict['T_credible_up2']], [result_dict['T_credible_low2']]), axis = 0)
   EResult = np.concatenate(([result_dict['E_array']], [result_dict['E_qhat_truth']], [result_dict['E_qhat_mean']],
      [result_dict['E_credible_up']], [result_dict['E_credible_low']],
      [result_dict['E_credible_up2']], [result_dict['E_credible_low2']]), axis = 0)

   np.savetxt('TResult.txt', TResult.T)
   np.savetxt('EResult.txt', EResult.T)

