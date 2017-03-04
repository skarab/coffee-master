function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6325\" class=\"headerLeftMenuInActive\"><a id=\"aID6325\" href=\"#\" OnMouseOver=\"link('_dir','event0',this)\" class=\"leftMenuLinkHeadInActive\">event</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID808\" class=\"leftMenuInActive\"><a id=\"aID808\" href=\"#\" OnMouseOver=\"link('_class','Event41582',this)\" class=\"leftMenuLinkInActive\">Event</a></div>\n");
document.write("<div id=\"divID809\" class=\"leftMenuInActive\"><a id=\"aID809\" href=\"#\" OnMouseOver=\"link('_class','EventCode41582',this)\" class=\"leftMenuLinkInActive\">EventCode</a></div>\n");
document.write("<div id=\"divID810\" class=\"leftMenuInActive\"><a id=\"aID810\" href=\"#\" OnMouseOver=\"link('_class','EventHandler41582',this)\" class=\"leftMenuLinkInActive\">EventHandler</a></div>\n");
document.write("<div id=\"divID811\" class=\"leftMenuInActive\"><a id=\"aID811\" href=\"#\" OnMouseOver=\"link('_class','EventHandlerMethod41582',this)\" class=\"leftMenuLinkInActive\">EventHandlerMethod</a></div>\n");
document.write("<div id=\"divID812\" class=\"leftMenuInActive\"><a id=\"aID812\" href=\"#\" OnMouseOver=\"link('_class','EventParameters41582',this)\" class=\"leftMenuLinkInActive\">EventParameters</a></div>\n");
document.write("<div id=\"divID813\" class=\"leftMenuInActive\"><a id=\"aID813\" href=\"#\" OnMouseOver=\"link('_class','EventQueue41582',this)\" class=\"leftMenuLinkInActive\">EventQueue</a></div>\n");
document.write("<div id=\"divID6167\" class=\"leftMenuInActive\"><a id=\"aID6167\" href=\"#\" OnMouseOver=\"link('_class','TreeNode0',this)\" class=\"leftMenuLinkInActive\">TreeNode</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6219\" class=\"leftMenuInActive\"><a id=\"aID6219\" href=\"#\" OnMouseOver=\"link('_member','EVENT_FLAG18069215',this)\" class=\"leftMenuLinkInActive\">EVENT_FLAG</a></div>\n");
document.write("<div id=\"divID6220\" class=\"leftMenuInActive\"><a id=\"aID6220\" href=\"#\" OnMouseOver=\"link('_member','EVENT_MESSAGE18069215',this)\" class=\"leftMenuLinkInActive\">EVENT_MESSAGE</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
