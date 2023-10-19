import { createApp } from 'vue'
import App from './App.vue'
import axios from 'axios'
import Toast from 'vue-toastification'
import 'vue-toastification/dist/index.css'
import router from './router'
import ToastPlugin from './plugins/toast'

createApp(App).use(router).use(ToastPlugin).mount('#app')
