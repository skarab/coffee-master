function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6287\" class=\"headerLeftMenuInActive\"><a id=\"aID6287\" href=\"#\" OnMouseOver=\"link('_dir','quaternion0',this)\" class=\"leftMenuLinkHeadInActive\">quaternion</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID746\" class=\"leftMenuInActive\"><a id=\"aID746\" href=\"#\" OnMouseOver=\"link('_class','Quaternion39014',this)\" class=\"leftMenuLinkInActive\">Quaternion</a></div>\n");
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
