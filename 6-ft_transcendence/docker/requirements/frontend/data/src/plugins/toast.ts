import { App } from 'vue'
import Toast from 'vue-toastification'
import 'vue-toastification/dist/index.css'

const ToastPlugin = {
  install: (app: App) => {
    app.use(Toast)
  }
}

export default ToastPlugin
