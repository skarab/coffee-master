function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6268\" class=\"headerLeftMenuInActive\"><a id=\"aID6268\" href=\"#\" OnMouseOver=\"link('_dir','container0',this)\" class=\"leftMenuLinkHeadInActive\">container</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6267\" class=\"leftMenuInActive\"><a id=\"aID6267\" href=\"#\" OnMouseOver=\"link('_dir','array/array0',this)\" class=\"leftMenuLinkInActive\">array</a></div>\n");
document.write("<div id=\"divID6269\" class=\"leftMenuInActive\"><a id=\"aID6269\" href=\"#\" OnMouseOver=\"link('_dir','list/list0',this)\" class=\"leftMenuLinkInActive\">list</a></div>\n");
document.write("<div id=\"divID6270\" class=\"leftMenuInActive\"><a id=\"aID6270\" href=\"#\" OnMouseOver=\"link('_dir','prow/prow0',this)\" class=\"leftMenuLinkInActive\">prow</a></div>\n");
document.write("<div id=\"divID6271\" class=\"leftMenuInActive\"><a id=\"aID6271\" href=\"#\" OnMouseOver=\"link('_dir','rope/rope0',this)\" class=\"leftMenuLinkInActive\">rope</a></div>\n");
document.write("<div id=\"divID6272\" class=\"leftMenuInActive\"><a id=\"aID6272\" href=\"#\" OnMouseOver=\"link('_dir','vector/vector0',this)\" class=\"leftMenuLinkInActive\">vector</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID727\" class=\"leftMenuInActive\"><a id=\"aID727\" href=\"#\" OnMouseOver=\"link('_class','Container6216',this)\" class=\"leftMenuLinkInActive\">Container<></a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Attributes</div>\n");
document.write("<div id=\"divID1125\" class=\"leftMenuInActive\"><a id=\"aID1125\" href=\"#\" OnMouseOver=\"link('_member','Container7578827',this)\" class=\"leftMenuLinkInActive\">Container</a></div>\n");
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
