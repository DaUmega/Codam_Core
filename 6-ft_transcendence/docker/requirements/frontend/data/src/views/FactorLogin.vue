<template>
  <div class="login">
    <BlackSection>
      <h1 class="title">Two factor authentication</h1>
      <div class="input-container">
        <input
          v-model.trim="verificationCode"
          type="text"
          maxlength="6"
          class="verification-input"
          @input="clearError"
        />
        <CustomButton class="custom-button" :handleClick="verifyTwoFactorSetup" :disabled="verificationCode.length !== 6">Verify</CustomButton>
      </div>
    </BlackSection>
  </div>
</template>

<script lang="ts">
import { defineComponent, ref } from 'vue'
import BlackSection from '../components/general/BlackSection.vue'
import CustomButton from '../components/general/CustomButton.vue'
import { API } from '@/plugins/axios'
import { useToast } from 'vue-toastification'

const siteIP = process.env.VUE_APP_SITE_IP
const apiKey = process.env.VUE_APP_SECRET

export default defineComponent({
  components: {
    BlackSection,
    CustomButton
  },
  data () {
    return {
      verificationCode: '',
      activeUser: '',
      buttonClicked: false,
      errorMessage: ''
    }
  },
  methods: {
    clearError () {
      // TODO What do we want here?
      this.errorMessage = ''
    },
    async verifyTwoFactorSetup () {
      this.buttonClicked = false
      try {
        const response = await API.post('/twofa', {
          username: this.activeUser,
          verificationCode: this.verificationCode
        })
        const data = response.data
        const toast = useToast()

        if (data) {
          // The verification was successful
          console.log('Verification successful')
          window.location.href = `http://${siteIP}/login?${apiKey}=${this.activeUser}`
        } else {
          // The verification failed
          console.log('Verification failed')
          toast.error('2FA Verification Failed')
        }
      } catch (error) {
        console.error('Error verifying two-factor setup:', error)
      }
    },
    parseUsername () {
      const urlParams = new URLSearchParams(window.location.search)
      const username = urlParams.get('user')

      if (username) {
        this.activeUser = username
      }
    }
  },
  created () {
    this.parseUsername()
  }
})
</script>

<style scoped>
.login {
  min-height: 100%;
  display: flex;
  flex-direction: column;
  justify-content: flex-start;
  align-items: center;
  padding: 20px;
  max-width: 400px;
  margin: 0 auto; /* Add this line to center the box */
}

.title {
  margin: 0;
  font-size: 24px;
  text-align: center;
  color: #71beba;
  margin-bottom: 2rem;
}

.input-container {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.verification-input {
  padding: 8px 12px;
  font-size: 18px;
  margin-bottom: 10px;
  text-align: center;
}

.error-message {
  color: red;
  margin-top: 10px;
}
</style>
