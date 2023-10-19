<template>
  <header class="header">
    <h1 class="title">The Awesome Pong Game!</h1>
    <div class="nav-container">
      <nav>
        <ul>
          <li><router-link to="/" class="nav-link">Home</router-link></li>
          <li><router-link to="/profile" class="nav-link">Profile</router-link></li>
          <li v-if="isLoggedIn"><router-link :to="friendsLink" class="nav-link">Friends</router-link></li>
          <li v-if="isLoggedIn"><router-link to="/chat" class="nav-link">Chat</router-link></li>
          <li v-if="isLoggedIn"><router-link to="/gamecentre" class="nav-link">Gamecentre</router-link></li>
          <li v-if="isLoggedIn"><router-link to="#" class="logout-button nav-link" @click="handleLogout">Logout</router-link></li>
          <li v-else><router-link to="/login" class="nav-link">Login</router-link></li>
        </ul>
      </nav>
    </div>
  </header>
</template>

<script lang="ts">
import { defineComponent, ref, onMounted, computed } from 'vue'
import { useRouter } from 'vue-router'

const siteIP = process.env.VUE_APP_SITE_IP

export default defineComponent({
  name: 'AppHeader',
  setup () {
    const isLoggedIn = ref(false)

    const checkLoginStatus = () => {
      isLoggedIn.value = !!sessionStorage.getItem('activeuser')
    }

    const router = useRouter()
    const handleLogout = () => {
      sessionStorage.removeItem('activeuser')
      isLoggedIn.value = false
      window.location.href = `http://${siteIP}/`
    }

    const friendsLink = computed(() => {
      const username = sessionStorage.getItem('activeuser')
      return {
        path: '/friends',
        query: { user: username }
      }
    })

    onMounted(() => {
      checkLoginStatus()
    })

    return {
      isLoggedIn,
      handleLogout,
      friendsLink
    }
  }
})
</script>

<style scoped>
.header {
  background-color: #000000;
  padding: 1rem;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.title {
  margin: 0;
  font-size: 24px;
  color: #71beba;
}

.nav-container {
  margin-top: 2rem;
}

nav ul {
  list-style: none;
  display: flex;
  justify-content: center;
  margin: 0;
  padding: 0;
}

nav li {
  margin: 0 1rem;
}

.nav-link {
  font-weight: bold;
  color: #2c3e50;
  text-decoration: none;
  &.router-link-exact-active {
    color: #71beba;
  }
}
</style>
