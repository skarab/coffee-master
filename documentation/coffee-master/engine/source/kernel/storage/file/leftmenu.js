function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6332\" class=\"headerLeftMenuInActive\"><a id=\"aID6332\" href=\"#\" OnMouseOver=\"link('_dir','file0',this)\" class=\"leftMenuLinkHeadInActive\">file</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID827\" class=\"leftMenuInActive\"><a id=\"aID827\" href=\"#\" OnMouseOver=\"link('_class','File35340',this)\" class=\"leftMenuLinkInActive\">File</a></div>\n");
document.write("<div id=\"divID828\" class=\"leftMenuInActive\"><a id=\"aID828\" href=\"#\" OnMouseOver=\"link('_class','FileAccess35340',this)\" class=\"leftMenuLinkInActive\">FileAccess</a></div>\n");
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
