<template>
  <div class="login">
    <BlackSection>
    <h1 class="title">Please login to your intra account</h1>
    <form name="login-form" @submit.prevent="submitForm">
      <CustomButton class="custom-button" :handleClick="handleLoginButtonClick">Login</CustomButton>
    </form>
    </BlackSection>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import CustomButton from '../components/general/CustomButton.vue'
import BlackSection from '../components/general/BlackSection.vue'

const apiKey = process.env.VUE_APP_SECRET
const siteIP = process.env.VUE_APP_SITE_IP

export default defineComponent({
  name: 'LoginPage',
  components: {
    BlackSection,
    CustomButton
  },
  methods: {
    handleLoginButtonClick () {
      // Redirect the user to the login page using string interpolation with backticks
      window.location.href = `http://${siteIP}:3000/${apiKey}/auth-secret/`
    },
    parseUsername () {
      const urlParams = new URLSearchParams(window.location.search)
      const username = urlParams.get(apiKey)

      if (username) {
        sessionStorage.setItem('activeuser', username)
        window.location.href = `http://${siteIP}/profile?user=${username}`
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

.login .custom-button {
  background-color: orange; /* change colour */
  padding: 10px 15px; /* Increase the padding to make the button bigger */
  font-size: 20px; /* Increase the font size of the button text */
  margin-top: 40px; /* Add margin-top to move the button down */
  font-weight: bold; /* Make the button text bold */
}

.custom-button:hover {
  background-color: darkorange; /* Change the background color to dark grey on hover */
}
</style>
