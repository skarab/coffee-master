function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6304\" class=\"headerLeftMenuInActive\"><a id=\"aID6304\" href=\"#\" OnMouseOver=\"link('_dir','info0',this)\" class=\"leftMenuLinkHeadInActive\">info</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID771\" class=\"leftMenuInActive\"><a id=\"aID771\" href=\"#\" OnMouseOver=\"link('_class','ObjectInfo53261',this)\" class=\"leftMenuLinkInActive\">ObjectInfo</a></div>\n");
document.write("<div id=\"divID6201\" class=\"leftMenuInActive\"><a id=\"aID6201\" href=\"#\" OnMouseOver=\"link('_class','TreeNode0',this)\" class=\"leftMenuLinkInActive\">TreeNode</a></div>\n");
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
