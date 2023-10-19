import { createRouter, createWebHistory, RouteRecordRaw } from 'vue-router'
import HomeView from '../views/HomeView.vue'
import CustomButton from './components/general/CustomButton.vue'

const routes: Array<RouteRecordRaw> = [
  {
    path: '/',
    name: 'home',
    component: HomeView
  },
  {
    path: '/gamecentre',
    name: 'Gamecentre',
    // route level code-splitting
    // this generates a separate chunk (settings.[hash].js) for this route
    // which is lazy-loaded when the route is visited.
    component: () => import(/* webpackChunkName: "settings" */ '../views/GameCentre.vue')
  },
  {
    path: '/friends',
    name: 'Friends',
    component: () => import(/* webpackChunkName: "friends" */ '../views/FriendsView.vue')
  },
  {
    path: '/profile',
    name: 'Profile',
    component: () => import(/* webpackChunkName: "profile" */ '../views/ProfileView.vue')
  },
  {
    path: '/chat',
    name: 'Chat',
    component: () => import(/* webpackChunkName: "chat" */ '../views/ChatView.vue')
  },
  {
    path: '/login',
    name: 'Login',
    component: () => import(/* webpackChunkName: "login" */ '../views/LoginView.vue')
  },
  {
    path: '/fa',
    name: '2FA',
    component: () => import(/* webpackChunkName: "2fa" */ '../views/FactorLogin.vue')
  }
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
})

export default router
